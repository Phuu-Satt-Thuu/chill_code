#include <SFML/Graphics.hpp> 
// Thư viện SFML dùng để xử lý đồ họa, bao gồm các hình ảnh, cửa sổ hiển thị, v.v.

#include "Fruit.h" 
// Bao gồm tệp tiêu đề `Fruit.h` để sử dụng lớp `Fruit` trong chương trình.

using namespace sfSnake;
// Sử dụng namespace `sfSnake` (giả định đã được định nghĩa trong tệp `Fruit.h` hoặc nơi khác).

const float Fruit::Radius = 5.f;
// Khai báo và định nghĩa hằng số `Radius` của lớp `Fruit` với giá trị 5.f (bán kính của quả).

Fruit::Fruit(sf::Vector2f position)
// Hàm khởi tạo của lớp `Fruit`, nhận tham số vị trí `position` dạng vector 2 chiều `sf::Vector2f`.
{
	shape_.setPosition(position);
	// Thiết lập vị trí của hình tròn (quả) dựa vào vị trí được truyền vào.

	shape_.setRadius(Fruit::Radius);
	// Thiết lập bán kính của hình tròn bằng giá trị hằng số `Radius`.

	shape_.setFillColor(sf::Color::Red);
	// Thiết lập màu sắc của hình tròn (quả) là màu đỏ.
}

void Fruit::render(sf::RenderWindow& window)
// Phương thức `render` dùng để vẽ hình quả lên cửa sổ hiển thị.
{
	window.draw(shape_);
	// Vẽ hình tròn (quả) lên cửa sổ đồ họa được truyền vào (window).
}

sf::FloatRect Fruit::getBounds() const
// Phương thức `getBounds` trả về khung hình chữ nhật bao quanh hình tròn (quả) dưới dạng `sf::FloatRect`.
{
	return shape_.getGlobalBounds();
	// Lấy khung bao quanh hình tròn dựa vào các tọa độ toàn cục (global).
}
