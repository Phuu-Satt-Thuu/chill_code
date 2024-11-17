#ifndef FRUIT_H
#define FRUIT_H
// Phần bảo vệ tệp tiêu đề: tránh việc định nghĩa lặp lại tệp tiêu đề `Fruit.h` trong quá trình biên dịch.

#include <SFML/Graphics.hpp>
// Bao gồm thư viện SFML để sử dụng các lớp liên quan đến đồ họa, ví dụ `sf::CircleShape`, `sf::RenderWindow`, v.v.

namespace sfSnake
	// Khai báo namespace `sfSnake` để nhóm các lớp, hàm liên quan trong trò chơi. Tránh xung đột tên với các namespace khác.
{
	class Fruit
		// Khai báo lớp `Fruit` đại diện cho quả trong trò chơi.
	{
	public:
		Fruit(sf::Vector2f position = sf::Vector2f(0, 0));
		// Hàm khởi tạo `Fruit`, với tham số mặc định là một vector tại tọa độ (0, 0).
		// Vector này dùng để xác định vị trí ban đầu của quả.

		void render(sf::RenderWindow& window);
		// Phương thức `render` dùng để vẽ quả lên cửa sổ đồ họa được truyền vào.

		sf::FloatRect getBounds() const;
		// Phương thức `getBounds` trả về khung hình chữ nhật bao quanh quả,
		// giúp kiểm tra va chạm hoặc tính toán vị trí.

	private:
		sf::CircleShape shape_;
		// Biến thành viên `shape_` là một hình tròn (CircleShape) để biểu diễn quả trên màn hình.

		static const float Radius;
		// Biến tĩnh hằng `Radius` lưu bán kính của quả, được dùng chung cho tất cả các đối tượng `Fruit`.
	};
}

#endif
// Kết thúc phần bảo vệ tệp tiêu đề.
