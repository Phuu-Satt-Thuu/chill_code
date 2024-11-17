#include <SFML/Graphics.hpp>
// Thư viện đồ họa SFML, cần thiết để tạo cửa sổ và vẽ đồ họa.

#include <memory>
// Thư viện để làm việc với con trỏ thông minh (shared_ptr, unique_ptr).

#include <iostream>
// Thư viện chuẩn để nhập xuất, ở đây có thể dùng để debug hoặc xuất thông tin ra màn hình console.

#include "Snake.h"
// Bao gồm file tiêu đề chứa định nghĩa của lớp `Snake`.

#include "Game.h"
// Bao gồm file tiêu đề của lớp `Game`, nơi chứa các thông tin về trò chơi.

#include "Fruit.h"
// Bao gồm file tiêu đề của lớp `Fruit`, đại diện cho quả mà con rắn ăn.

#include "SnakeNode.h"
// Bao gồm file tiêu đề của lớp `SnakeNode`, đại diện cho các phần của con rắn.

#include "GameOverScreen.h"
// Bao gồm file tiêu đề của lớp `GameOverScreen`, màn hình hiển thị khi trò chơi kết thúc.

using namespace sfSnake;
// Sử dụng không gian tên `sfSnake` để rút ngắn các tên lớp, ví dụ: `GameScreen` thay vì `sfSnake::GameScreen`.

const int Snake::InitialSize = 5;
// Khởi tạo hằng số `InitialSize` là kích thước ban đầu của con rắn.

Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
// Khởi tạo đối tượng `Snake`, thiết lập hướng di chuyển ban đầu là "lên" và chưa va chạm vào chính nó.
{
    initNodes(); // Gọi phương thức khởi tạo các phần tử của con rắn.

    pickupBuffer_.loadFromFile("eat.mp3");
    // Tải file âm thanh "eat.mp3" cho hiệu ứng ăn quả.

    pickupSound_.setBuffer(pickupBuffer_);
    pickupSound_.setVolume(30);
    // Gán âm thanh cho đối tượng `pickupSound_` và điều chỉnh âm lượng.

    dieBuffer_.loadFromFile("die.wav");
    // Tải file âm thanh "die.wav" cho hiệu ứng chết.

    dieSound_.setBuffer(dieBuffer_);
    dieSound_.setVolume(50);
    // Gán âm thanh cho đối tượng `dieSound_` và điều chỉnh âm lượng.
}

void Snake::initNodes()
// Khởi tạo các nút của con rắn.
{
    for (int i = 0; i < Snake::InitialSize; ++i)
    {
        nodes_.push_back(SnakeNode(sf::Vector2f(
            Game::Width / 2 - SnakeNode::Width / 2, // Tính toán vị trí x của nút.
            Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i)))); // Tính toán vị trí y của nút.
    }
}

void Snake::handleInput()
// Xử lý đầu vào từ người chơi.
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        direction_ = Direction::Up; // Nếu nhấn phím "Up", thay đổi hướng lên.

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        direction_ = Direction::Down; // Nếu nhấn phím "Down", thay đổi hướng xuống.

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        direction_ = Direction::Left; // Nếu nhấn phím "Left", thay đổi hướng trái.

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        direction_ = Direction::Right; // Nếu nhấn phím "Right", thay đổi hướng phải.
}

void Snake::update(sf::Time delta)
// Cập nhật trạng thái của con rắn theo thời gian.
{
    move(); // Di chuyển con rắn.
    checkEdgeCollisions(); // Kiểm tra va chạm với biên.
    checkSelfCollisions(); // Kiểm tra va chạm với chính con rắn.
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
// Kiểm tra va chạm với quả.
{
    decltype(fruits.begin()) toRemove = fruits.end(); // Khởi tạo biến `toRemove` dùng để lưu trữ quả sẽ bị xóa.

    for (auto it = fruits.begin(); it != fruits.end(); ++it)
    {
        if (it->getBounds().intersects(nodes_[0].getBounds()))
            toRemove = it; // Nếu quả va chạm với đầu con rắn, lưu lại quả đó.
    }

    if (toRemove != fruits.end())
    {
        pickupSound_.play(); // Phát âm thanh khi ăn quả.
        grow(); // Tăng kích thước con rắn.
        fruits.erase(toRemove); // Xóa quả đã bị ăn khỏi danh sách.
    }
}

void Snake::grow()
// Mở rộng con rắn khi ăn quả.
{
    switch (direction_)
    {
    case Direction::Up:
        nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
            nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height)));
        break; // Tạo thêm một phần tử con rắn ở trên.
    case Direction::Down:
        nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
            nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height)));
        break; // Tạo thêm một phần tử con rắn ở dưới.
    case Direction::Left:
        nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Width,
            nodes_[nodes_.size() - 1].getPosition().y)));
        break; // Tạo thêm một phần tử con rắn bên trái.
    case Direction::Right:
        nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width,
            nodes_[nodes_.size() - 1].getPosition().y)));
        break; // Tạo thêm một phần tử con rắn bên phải.
    }
}

unsigned Snake::getSize() const
// Trả về kích thước hiện tại của con rắn.
{
    return nodes_.size();
}

bool Snake::hitSelf() const
// Kiểm tra xem con rắn có va chạm với chính nó không.
{
    return hitSelf_;
}

void Snake::checkSelfCollisions()
// Kiểm tra va chạm của con rắn với chính nó.
{
    SnakeNode& headNode = nodes_[0]; // Lấy phần đầu của con rắn.

    for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
    {
        if (headNode.getBounds().intersects(nodes_[i].getBounds()))
        {
            dieSound_.play(); // Phát âm thanh khi con rắn va chạm với chính nó.
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds())); // Dừng lại trong một khoảng thời gian sau khi chết.
            hitSelf_ = true; // Đánh dấu con rắn đã va chạm với chính nó.
        }
    }
}

void Snake::checkEdgeCollisions()
// Kiểm tra va chạm với biên của cửa sổ trò chơi.
{
    SnakeNode& headNode = nodes_[0]; // Lấy phần đầu của con rắn.

    if (headNode.getPosition().x <= 0)
        headNode.setPosition(Game::Width, headNode.getPosition().y); // Nếu con rắn ra ngoài bên trái, tái xuất bên phải.
    else if (headNode.getPosition().x >= Game::Width)
        headNode.setPosition(0, headNode.getPosition().y); // Nếu con rắn ra ngoài bên phải, tái xuất bên trái.
    else if (headNode.getPosition().y <= 0)
        headNode.setPosition(headNode.getPosition().x, Game::Height); // Nếu con rắn ra ngoài trên, tái xuất dưới.
    else if (headNode.getPosition().y >= Game::Height)
        headNode.setPosition(headNode.getPosition().x, 0); // Nếu con rắn ra ngoài dưới, tái xuất trên.
}

void Snake::move()
// Di chuyển con rắn.
{
    for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
    {
        nodes_[i].setPosition(nodes_.at(i - 1).getPosition()); // Cập nhật vị trí các phần tử rắn từ cuối lên đầu.
    }

    switch (direction_)
    {
    case Direction::Up:
        nodes_[0].move(0, -SnakeNode::Height); // Di chuyển đầu rắn lên.
        break;
    case Direction::Down:
        nodes_[0].move(0, SnakeNode::Height); // Di chuyển đầu rắn xuống.
        break;
    case Direction::Left:
        nodes_[0].move(-SnakeNode::Width, 0); // Di chuyển đầu rắn sang trái.
        break;
    case Direction::Right:
        nodes_[0].move(SnakeNode::Width, 0); // Di chuyển đầu rắn sang phải.
        break;
    }
}

void Snake::render(sf::RenderWindow& window)
// Vẽ con rắn lên cửa sổ.
{
    for (auto node : nodes_)
        node.render(window); // Vẽ tất cả các phần tử con rắn.
}
