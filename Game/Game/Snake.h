#ifndef SNAKE_H // Đảm bảo rằng file này chỉ được bao gồm một lần trong suốt quá trình biên dịch
#define SNAKE_H

#include <SFML/Graphics.hpp>  // Bao gồm thư viện đồ họa SFML để làm việc với đồ họa (ví dụ như vẽ hình ảnh, đối tượng)
#include <SFML/Audio.hpp>     // Bao gồm thư viện âm thanh SFML để làm việc với âm thanh (như phát nhạc, hiệu ứng âm thanh)
#include <vector>             // Bao gồm thư viện vector của C++ để sử dụng kiểu dữ liệu vector (mảng động)

#include "SnakeNode.h"        // Bao gồm định nghĩa lớp SnakeNode (để đại diện cho từng phần của con rắn)
#include "Fruit.h"            // Bao gồm định nghĩa lớp Fruit (để đại diện cho quả ăn trong game)

namespace sfSnake             // Đặt mã nguồn vào trong không gian tên sfSnake để tránh xung đột tên
{
	// Định nghĩa một kiểu enum Direction để xác định các hướng mà con rắn có thể di chuyển
	enum class Direction
	{
		Left, Right, Up, Down   // Các giá trị của hướng: Trái, Phải, Lên, Xuống
	};

	// Lớp Snake đại diện cho con rắn trong trò chơi
	class Snake
	{
	public:
		// Hàm khởi tạo của lớp Snake
		Snake();

		// Xử lý đầu vào từ bàn phím (các phím di chuyển)
		void handleInput();

		// Cập nhật trạng thái của con rắn trong mỗi frame (sử dụng thời gian delta)
		void update(sf::Time delta);

		// Vẽ con rắn lên cửa sổ đồ họa
		void render(sf::RenderWindow& window);

		// Kiểm tra xem con rắn có ăn quả không (kiểm tra va chạm với các quả)
		void checkFruitCollisions(std::vector<Fruit>& fruits);

		// Kiểm tra xem con rắn có va chạm với chính nó không
		bool hitSelf() const;

		// Lấy kích thước (số lượng các phần tử của con rắn)
		unsigned getSize() const;

	private:
		// Hàm di chuyển con rắn
		void move();

		// Hàm làm con rắn dài ra khi ăn quả
		void grow();

		// Kiểm tra xem con rắn có va chạm với các cạnh của màn hình không
		void checkEdgeCollisions();

		// Kiểm tra xem con rắn có va chạm với chính nó không
		void checkSelfCollisions();

		// Khởi tạo các phần tử của con rắn (các node)
		void initNodes();

		// Biến lưu trữ trạng thái va chạm với chính nó (true nếu va chạm)
		bool hitSelf_;

		// Vị trí hiện tại của con rắn
		sf::Vector2f position_;

		// Hướng di chuyển của con rắn (Left, Right, Up, Down)
		Direction direction_;

		// Các đối tượng âm thanh: hiệu ứng âm thanh khi ăn quả và khi chết
		sf::SoundBuffer pickupBuffer_;
		sf::Sound pickupSound_;

		sf::SoundBuffer dieBuffer_;
		sf::Sound dieSound_;

		// Mảng động các node của con rắn
		std::vector<SnakeNode> nodes_;

		// Kích thước ban đầu của con rắn (khi khởi tạo)
		static const int InitialSize;
	};
}

#endif
