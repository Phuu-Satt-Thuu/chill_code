#include <SFML/Graphics.hpp>  // Bao gồm thư viện đồ họa SFML để làm việc với các đối tượng đồ họa như hình chữ nhật

#include "SnakeNode.h"         // Bao gồm định nghĩa của lớp SnakeNode, đại diện cho một phần của con rắn

using namespace sfSnake;      // Sử dụng không gian tên sfSnake để tránh xung đột tên với các lớp khác

// Khởi tạo các giá trị hằng số cho chiều rộng và chiều cao của mỗi node của con rắn
const float SnakeNode::Width = 10.f;    // Chiều rộng của mỗi node (phần của con rắn)
const float SnakeNode::Height = 10.f;   // Chiều cao của mỗi node (phần của con rắn)

// Hàm khởi tạo của lớp SnakeNode, nhận vào một vị trí (sf::Vector2f) và khởi tạo các thuộc tính
SnakeNode::SnakeNode(sf::Vector2f position)
	: position_(position)  // Khởi tạo vị trí của node từ đối số position
{
	// Thiết lập các thuộc tính của hình chữ nhật đại diện cho node
	shape_.setPosition(position_);                // Đặt vị trí ban đầu của hình chữ nhật (node)
	shape_.setFillColor(sf::Color::Green);        // Đặt màu sắc fill (màu bên trong) của hình chữ nhật là màu xanh
	shape_.setSize(sf::Vector2f(SnakeNode::Width, SnakeNode::Height));  // Đặt kích thước hình chữ nhật bằng chiều rộng và chiều cao đã định nghĩa
	shape_.setOutlineColor(sf::Color::White);     // Đặt màu viền của hình chữ nhật là màu trắng
	shape_.setOutlineThickness(-1.f);             // Đặt độ dày viền của hình chữ nhật (có thể điều chỉnh độ dày viền)
}

// Hàm để thay đổi vị trí của node bằng cách truyền vào một đối tượng sf::Vector2f mới
void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;               // Cập nhật vị trí của node
	shape_.setPosition(position_);      // Cập nhật vị trí của hình chữ nhật (node) trên màn hình
}

// Hàm để thay đổi vị trí của node bằng cách truyền vào các giá trị x và y (float)
void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;                    // Cập nhật tọa độ x của vị trí node
	position_.y = y;                    // Cập nhật tọa độ y của vị trí node
	shape_.setPosition(position_);      // Cập nhật vị trí của hình chữ nhật (node) trên màn hình
}

// Hàm để di chuyển node (thay đổi vị trí của node theo các độ dịch chuyển x và y)
void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;             // Cộng thêm giá trị xOffset vào tọa độ x của node
	position_.y += yOffset;             // Cộng thêm giá trị yOffset vào tọa độ y của node
	shape_.setPosition(position_);      // Cập nhật vị trí của hình chữ nhật (node) trên màn hình
}

// Hàm trả về vùng giới hạn (bounding box) của hình chữ nhật (node) dưới dạng sf::FloatRect
sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();    // Lấy và trả về phạm vi toàn cầu (bounding box) của hình chữ nhật (node)
}

// Hàm trả về vị trí hiện tại của node dưới dạng sf::Vector2f
sf::Vector2f SnakeNode::getPosition() const
{
	return position_;  // Trả về vị trí của node
}

// Hàm vẽ node lên cửa sổ đồ họa
void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);  // Vẽ hình chữ nhật (node) lên cửa sổ đồ họa
}
