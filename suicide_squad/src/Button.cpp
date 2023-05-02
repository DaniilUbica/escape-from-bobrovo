#include "..\include\UI\Button.h"

bool Button::checkMouseInButton(sf::Vector2i coords) {
    sf::FloatRect border_rect = border.getGlobalBounds();

    return coords.x > border_rect.left && coords.x < border_rect.width + border_rect.left
        && coords.y > border_rect.top && coords.y < border_rect.top + border_rect.height && isActive;
}

Button::Button(float x, float y, float w, float h, sf::Vector3i border_color, sf::Vector3i button_color, sf::Vector3i text_color, sf::Text text) {
    this->text = text;
    this->border_color = border_color;
    this->button_color = button_color;
    this->text_color = text_color;

    border = sf::RectangleShape(sf::Vector2f(w + BORDER_SIZE, h + BORDER_SIZE));
    button = sf::RectangleShape(sf::Vector2f(w, h));

    border.setFillColor(sf::Color(border_color.x, border_color.y, border_color.z));
    button.setFillColor(sf::Color(button_color.x, button_color.y, button_color.z));

    border.setPosition(x - BORDER_SIZE / 2, y - BORDER_SIZE / 2);
    button.setPosition(x, y);

    this->text.setFillColor(sf::Color(text_color.x, text_color.y, text_color.z));
    this->text.setCharacterSize(15);
    sf::FloatRect t_bounds = this->text.getLocalBounds();
    this->text.setPosition(x + w / 2 - t_bounds.width / 2, y + h / 2 - t_bounds.height / 2 - t_bounds.top);
}

void Button::Update(sf::RenderWindow& window) {
    if (checkMouseInButton(sf::Mouse::getPosition(window)) || !isActive) {
        border.setFillColor(sf::Color(border_color.x, border_color.y, border_color.z, 127));
        button.setFillColor(sf::Color(button_color.x, button_color.y, button_color.z, 127));
        text.setFillColor(sf::Color(text_color.x, text_color.y, text_color.z, 127));
    }
    else {
        border.setFillColor(sf::Color(border_color.x, border_color.y, border_color.z));
        button.setFillColor(sf::Color(button_color.x, button_color.y, button_color.z));
        text.setFillColor(sf::Color(text_color.x, text_color.y, text_color.z));
    }
}

bool Button::checkClick(sf::RenderWindow& window, sf::Event& event) {
    if (checkMouseInButton(sf::Mouse::getPosition(window)) && event.type == sf::Event::MouseButtonReleased
        && event.mouseButton.button == sf::Mouse::Left) {
        return true;
    }
    return false;
}

void Button::drawButton(sf::RenderWindow& window) {
    window.draw(border);
    window.draw(button);
    window.draw(text);
}

void Button::setActive(bool a) {
    isActive = a;
}

bool Button::getActive() {
    return isActive;
}
