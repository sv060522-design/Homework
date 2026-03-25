#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include <iostream>

class Widget {
protected:
    sf::RenderWindow& mRenderWindow;
public:
    Widget(sf::RenderWindow& window) : mRenderWindow(window) {}
    virtual ~Widget() = default;
    virtual void draw() = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;
};

class Button : public Widget {
private:
    sf::Color mDefaultColor {179, 230, 255};
    sf::Color mHoverColor   {128, 212, 255};
    sf::Color mPressedColor {  0, 136, 204};
    sf::RectangleShape mShape {};
    sf::Text mText {};
    bool mIsPressed {false};

    void onMousePressed(const sf::Event& event) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (mShape.getGlobalBounds().contains(mousePos)) {
                mIsPressed = true;
                mShape.setFillColor(mPressedColor);
            }
        }
    }

    void onMouseMove(const sf::Event& event) {
        if (mIsPressed) return;
        sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        if (mShape.getGlobalBounds().contains(mousePos))
            mShape.setFillColor(mHoverColor);
        else
            mShape.setFillColor(mDefaultColor);
    }

    bool onMouseReleased(const sf::Event& event) {
        if (!mIsPressed) return false;
        mIsPressed = false;
        sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (mShape.getGlobalBounds().contains(mousePos)) {
            mShape.setFillColor(mHoverColor);
            return true;
        }
        mShape.setFillColor(mDefaultColor);
        return false;
    }

public:
    Button(sf::RenderWindow& window, sf::FloatRect rect, sf::Font& font, const sf::String& textData) 
        : Widget(window) {
        mShape.setPosition({rect.left, rect.top});
        mShape.setSize({rect.width, rect.height});
        mShape.setFillColor(mDefaultColor);
        mText.setFont(font);
        mText.setString(textData);
        mText.setCharacterSize(24);
        mText.setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = mText.getLocalBounds();
        mText.setOrigin({textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f});
        mText.setPosition(mShape.getPosition() + mShape.getSize() / 2.0f);
    }

    void draw() override {
        mRenderWindow.draw(mShape);
        mRenderWindow.draw(mText);
    }

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            onMousePressed(event);
        } else if (event.type == sf::Event::MouseMoved) {
            onMouseMove(event);
        } else if (event.type == sf::Event::MouseButtonReleased) {
            return onMouseReleased(event);
        }
        return false;
    }
};

class Slider : public Widget {
protected:
    sf::RectangleShape mTrackShape {};
    sf::RectangleShape mThumbShape {};
    bool mIsPressed {false};

    void setRestrictedThumbPosition(sf::Vector2f pos) {
        float minX = mTrackShape.getPosition().x - mTrackShape.getSize().x / 2.0f;
        float maxX = mTrackShape.getPosition().x + mTrackShape.getSize().x / 2.0f;
        if (pos.x < minX) pos.x = minX;
        if (pos.x > maxX) pos.x = maxX;
        mThumbShape.setPosition({pos.x, mThumbShape.getPosition().y});
    }

public:
    Slider(sf::RenderWindow& window, sf::Vector2f centerPos, sf::Vector2f trackSize, sf::Vector2f thumbSize) 
        : Widget(window) {
        mTrackShape.setSize(trackSize);
        mTrackShape.setOrigin(trackSize / 2.0f);
        mTrackShape.setPosition(centerPos);
        mTrackShape.setFillColor({200, 200, 220});
        mThumbShape.setSize(thumbSize);
        mThumbShape.setOrigin(thumbSize / 2.0f);
        mThumbShape.setPosition(centerPos);
        mThumbShape.setFillColor({150, 150, 240});
    }

    void draw() override {
        mRenderWindow.draw(mTrackShape);
        mRenderWindow.draw(mThumbShape);
    }

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (mThumbShape.getGlobalBounds().contains(mousePos)) {
                mIsPressed = true;
                return true;
            }
        } else if (event.type == sf::Event::MouseMoved && mIsPressed) {
            sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            setRestrictedThumbPosition(mousePos);
        } else if (event.type == sf::Event::MouseButtonReleased) {
            mIsPressed = false;
        }
        return false;
    }
};

class Draggable : public Widget {
protected:
    sf::RectangleShape mShape {};
    bool mIsDragged {false};
    sf::Vector2f mOffset {0.0f, 0.0f};

public:
    Draggable(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size, sf::Color color)
        : Widget(window) {
        mShape.setPosition(pos);
        mShape.setSize(size);
        mShape.setFillColor(color);
    }

    void draw() override {
        mRenderWindow.draw(mShape);
    }

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            if (mShape.getGlobalBounds().contains(mousePos)) {
                mIsDragged = true;
                mOffset = mousePos - mShape.getPosition();
                return true;
            }
        } else if (event.type == sf::Event::MouseMoved && mIsDragged) {
            sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            mShape.setPosition(mousePos - mOffset);
        } else if (event.type == sf::Event::MouseButtonReleased) {
            mIsDragged = false;
        }
        return false;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Unique Pointers");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("sourceCodePro.ttf")) return 1;

    std::vector<std::unique_ptr<Widget>> widgets;
    widgets.push_back(std::make_unique<Button>(window, sf::FloatRect(50, 50, 150, 50), font, "Click Me"));
    widgets.push_back(std::make_unique<Slider>(window, sf::Vector2f(400, 400), sf::Vector2f(300, 10), sf::Vector2f(20, 40)));
    widgets.push_back(std::make_unique<Draggable>(window, sf::Vector2f(100, 200), sf::Vector2f(100, 100), sf::Color::Blue));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            for (auto& w : widgets) w->handleEvent(event);
        }
        window.clear(sf::Color::White);
        for (auto& w : widgets) w->draw();
        window.display();
    }
    return 0;
}