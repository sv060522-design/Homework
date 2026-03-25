#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Node;
class SkillTree;

class SkillTree
{
protected:
    std::shared_ptr<Node> root;
    int points;
    sf::Font font;

    bool loadFont()
    {
        const char* f[] = {
            "fonts/arial.ttf",
            "arial.ttf",
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/truetype/liberation2/LiberationSans-Regular.ttf",
            "/usr/share/fonts/truetype/freefont/FreeSans.ttf",
            "C:/Windows/Fonts/arial.ttf"
        };

        for (const char* x : f)
        {
            if (font.loadFromFile(x))
                return true;
        }

        return false;
    }

public:
    SkillTree(int p = 10) : points{p}
    {
        if (!loadFont())
        {
            std::cout << "Error! Can't load font" << std::endl;
            std::exit(1);
        }
    }

    virtual ~SkillTree() = default;
    virtual std::shared_ptr<Node> buildTree() = 0;

    bool spendPoint()
    {
        if (points <= 0)
            return false;

        --points;
        return true;
    }

    void refundPoint()
    {
        ++points;
    }

    void onMousePressed(sf::Vector2f m, sf::Mouse::Button b);
    void draw(sf::RenderWindow& w) const;
};

class Line
{
private:
    sf::Vertex v[4];
    bool ok;

public:
    Line(sf::Vector2f p1, sf::Vector2f p2, sf::Color c, float t) : ok(false)
    {
        sf::Vector2f d = p2 - p1;
        float l = std::sqrt(d.x * d.x + d.y * d.y);

        if (l <= 0.f)
            return;

        sf::Vector2f u{d.x / l, d.y / l};
        sf::Vector2f n{-u.y, u.x};
        sf::Vector2f o{n.x * (t / 2.f), n.y * (t / 2.f)};

        v[0].position = p1 + o;
        v[1].position = p2 + o;
        v[2].position = p2 - o;
        v[3].position = p1 - o;

        for (int i = 0; i < 4; ++i)
            v[i].color = c;

        ok = true;
    }

    void draw(sf::RenderWindow& w) const
    {
        if (ok)
            w.draw(v, 4, sf::Quads);
    }
};

class Node
{
public:
    enum class State
    {
        Blocked,
        Unblocked,
        Activated
    };

protected:
    sf::Vector2f p{0.f, 0.f};
    State st{State::Blocked};

    sf::Color c0{40, 40, 40};
    sf::Color c1{80, 80, 40};
    sf::Color c2{160, 160, 40};

    std::vector<std::shared_ptr<Node>> ch;

    void kidsBlock()
    {
        for (const auto& x : ch)
            x->block();
    }

    void kidsUnblock()
    {
        for (const auto& x : ch)
            x->unblock();
    }

    void kidsPress(sf::Vector2f m, sf::Mouse::Button b, SkillTree& t)
    {
        for (const auto& x : ch)
            x->onMousePressed(m, b, t);
    }

    sf::Color curColor() const
    {
        if (st == State::Unblocked)
            return c1;
        if (st == State::Activated)
            return c2;
        return c0;
    }

public:
    Node(sf::Vector2f pos) : p{pos} {}
    virtual ~Node() = default;

    void addChild(const std::shared_ptr<Node>& x)
    {
        ch.push_back(x);
    }

    void unblock()
    {
        st = State::Unblocked;
    }

    virtual void block()
    {
        st = State::Blocked;
        kidsBlock();
    }

    sf::Vector2f getPosition() const
    {
        return p;
    }

    virtual bool collisionTest(sf::Vector2f m) const = 0;
    virtual void onMousePressed(sf::Vector2f m, sf::Mouse::Button b, SkillTree& t) = 0;
    virtual void draw(sf::RenderWindow& w, const sf::Font& f) const = 0;
};

class HitNode : public Node
{
protected:
    sf::Texture tx;
    sf::Sprite sp;
    float r{24.f};

public:
    HitNode(sf::Vector2f pos) : Node{pos} {}

    virtual sf::String getIconPath() const = 0;

    void loadTexture()
    {
        sf::String path = getIconPath();

        if (!tx.loadFromFile(path))
        {
            std::cout << "Error! Can't load file " << path.toAnsiString() << std::endl;
            std::exit(1);
        }

        sp.setTexture(tx);
        sp.setOrigin({r, r});
        sp.setPosition(p);
    }

    bool collisionTest(sf::Vector2f m) const override
    {
        sf::Vector2f d = p - m;
        return d.x * d.x + d.y * d.y < r * r;
    }

    void onMousePressed(sf::Vector2f m, sf::Mouse::Button b, SkillTree& t) override
    {
        if (st != State::Blocked && collisionTest(m) && b == sf::Mouse::Left)
        {
            if (st == State::Unblocked)
            {
                if (t.spendPoint())
                {
                    st = State::Activated;
                    kidsUnblock();
                }
            }
            else if (st == State::Activated)
            {
                st = State::Unblocked;
                t.refundPoint();
                kidsBlock();
            }
        }

        kidsPress(m, b, t);
    }

    void draw(sf::RenderWindow& w, const sf::Font& f) const override
    {
        for (const auto& x : ch)
        {
            Line l{p, x->getPosition(), curColor(), 2.f};
            l.draw(w);
            x->draw(w, f);
        }

        sf::CircleShape sh(r);
        sh.setOrigin({r, r});
        sh.setPosition(p);
        sh.setFillColor(curColor());
        w.draw(sh);
        w.draw(sp);
    }
};

class BombSkillNode : public HitNode
{
public:
    BombSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_bomb.png";
    }
};

class SpikesSkillNode : public HitNode
{
public:
    SpikesSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_spikes.png";
    }
};

class LightningSkillNode : public HitNode
{
public:
    LightningSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_lightning.png";
    }
};

class EyeSkillNode : public HitNode
{
public:
    EyeSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_eye.png";
    }
};

class ClawsSkillNode : public HitNode
{
public:
    ClawsSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_claws.png";
    }
};

class ShieldSkillNode : public HitNode
{
public:
    ShieldSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_shield.png";
    }
};

class SwordSkillNode : public HitNode
{
public:
    SwordSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_sword.png";
    }
};

class ShurikenSkillNode : public HitNode
{
public:
    ShurikenSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_shuriken.png";
    }
};

class WindSkillNode : public HitNode
{
public:
    WindSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_shuriken.png";
    }
};

class MeteoriteSkillNode : public HitNode
{
public:
    MeteoriteSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_meteorite.png";
    }
};

class HandSkillNode : public HitNode
{
public:
    HandSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_hand.png";
    }
};

class EarthquakeSkillNode : public HitNode
{
public:
    EarthquakeSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_earthquake.png";
    }
};

class FireballSkillNode : public HitNode
{
public:
    FireballSkillNode(sf::Vector2f pos) : HitNode{pos}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_fireball.png";
    }
};

class AccumulativeNode : public Node
{
protected:
    sf::Texture tx;
    sf::Sprite sp;
    float a{52.f};
    int lv{0};
    int mx{3};

public:
    AccumulativeNode(sf::Vector2f pos, int m = 3) : Node{pos}, mx{m} {}

    virtual sf::String getIconPath() const = 0;

    void loadTexture()
    {
        sf::String path = getIconPath();

        if (!tx.loadFromFile(path))
        {
            std::cout << "Error! Can't load file " << path.toAnsiString() << std::endl;
            std::exit(1);
        }

        sp.setTexture(tx);
        sp.setOrigin({24.f, 24.f});
        sp.setPosition(p);
    }

    bool collisionTest(sf::Vector2f m) const override
    {
        float h = a / 2.f;
        return std::fabs(m.x - p.x) <= h && std::fabs(m.y - p.y) <= h;
    }

    void onMousePressed(sf::Vector2f m, sf::Mouse::Button b, SkillTree& t) override
    {
        if (st != State::Blocked && collisionTest(m))
        {
            if (b == sf::Mouse::Left)
            {
                if (st == State::Unblocked)
                {
                    if (t.spendPoint())
                    {
                        st = State::Activated;
                        lv = 1;
                        kidsUnblock();
                    }
                }
                else if (st == State::Activated)
                {
                    if (lv < mx && t.spendPoint())
                        ++lv;
                }
            }
            else if (b == sf::Mouse::Right)
            {
                if (st == State::Activated)
                {
                    --lv;
                    t.refundPoint();

                    if (lv == 0)
                    {
                        st = State::Unblocked;
                        kidsBlock();
                    }
                }
            }
        }

        kidsPress(m, b, t);
    }

    void draw(sf::RenderWindow& w, const sf::Font& f) const override
    {
        for (const auto& x : ch)
        {
            Line l{p, x->getPosition(), curColor(), 2.f};
            l.draw(w);
            x->draw(w, f);
        }

        sf::RectangleShape sh(sf::Vector2f{a, a});
        sh.setOrigin({a / 2.f, a / 2.f});
        sh.setPosition(p);
        sh.setFillColor(curColor());
        w.draw(sh);
        w.draw(sp);

        sf::Text tx2;
        tx2.setFont(f);
        tx2.setCharacterSize(14);
        tx2.setFillColor(sf::Color::White);
        tx2.setString(std::to_string(lv) + " / " + std::to_string(mx));

        sf::FloatRect b = tx2.getLocalBounds();
        tx2.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        tx2.setPosition(p.x, p.y + a / 2.f + 12.f);
        w.draw(tx2);
    }
};

class RectSwordSkillNode : public AccumulativeNode
{
public:
    RectSwordSkillNode(sf::Vector2f pos) : AccumulativeNode{pos, 3}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_rect_sword.png";
    }
};

class RectChainSkillNode : public AccumulativeNode
{
public:
    RectChainSkillNode(sf::Vector2f pos) : AccumulativeNode{pos, 3}
    {
        loadTexture();
    }

    sf::String getIconPath() const override
    {
        return "icons/icon_rect_chain.png";
    }
};

class MageSkillTree : public SkillTree
{
public:
    MageSkillTree() : SkillTree{10}
    {
        root = buildTree();

        if (root)
            root->unblock();
    }

    std::shared_ptr<Node> buildTree() override
    {
        std::shared_ptr<Node> r = std::make_shared<LightningSkillNode>(sf::Vector2f{400.f, 550.f});
        std::shared_ptr<Node> a = std::make_shared<ShurikenSkillNode>(sf::Vector2f{200.f, 400.f});
        std::shared_ptr<Node> b = std::make_shared<BombSkillNode>(sf::Vector2f{400.f, 400.f});
        std::shared_ptr<Node> c = std::make_shared<EyeSkillNode>(sf::Vector2f{600.f, 400.f});

        r->addChild(a);
        r->addChild(b);
        r->addChild(c);

        a->addChild(std::make_shared<ShieldSkillNode>(sf::Vector2f{120.f, 240.f}));
        std::shared_ptr<Node> a2 = std::make_shared<RectSwordSkillNode>(sf::Vector2f{260.f, 240.f});
        a->addChild(a2);
        a2->addChild(std::make_shared<ClawsSkillNode>(sf::Vector2f{260.f, 100.f}));

        b->addChild(std::make_shared<HandSkillNode>(sf::Vector2f{340.f, 240.f}));
        std::shared_ptr<Node> b2 = std::make_shared<FireballSkillNode>(sf::Vector2f{480.f, 240.f});
        b->addChild(b2);
        b2->addChild(std::make_shared<WindSkillNode>(sf::Vector2f{420.f, 100.f}));
        b2->addChild(std::make_shared<MeteoriteSkillNode>(sf::Vector2f{540.f, 100.f}));

        std::shared_ptr<Node> c1 = std::make_shared<RectChainSkillNode>(sf::Vector2f{540.f, 240.f});
        c->addChild(c1);
        c->addChild(std::make_shared<SpikesSkillNode>(sf::Vector2f{680.f, 240.f}));
        c1->addChild(std::make_shared<EarthquakeSkillNode>(sf::Vector2f{540.f, 100.f}));

        return r;
    }
};

void SkillTree::onMousePressed(sf::Vector2f m, sf::Mouse::Button b)
{
    if (root)
        root->onMousePressed(m, b, *this);
}

void SkillTree::draw(sf::RenderWindow& w) const
{
    if (root)
        root->draw(w, font);

    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(20);
    t.setFillColor(sf::Color::White);
    t.setPosition(15.f, 10.f);
    t.setString("Free points: " + std::to_string(points));
    w.draw(t);
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Skill Tree", sf::Style::Close, settings);
    window.setFramerateLimit(60);

    MageSkillTree t;

    while (window.isOpen())
    {
        sf::Event e;

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if (e.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f m = window.mapPixelToCoords({e.mouseButton.x, e.mouseButton.y});
                t.onMousePressed(m, e.mouseButton.button);
            }
        }

        window.clear(sf::Color::Black);
        t.draw(window);
        window.display();
    }

    return 0;
}