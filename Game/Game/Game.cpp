#include <SFML/Graphics.hpp>
// Thư viện SFML để xử lý đồ họa.

#include <memory>
// Thư viện C++ cho việc quản lý con trỏ thông minh (`std::shared_ptr`).

#include "MenuScreen.h"
// Bao gồm tệp tiêu đề `MenuScreen.h` để sử dụng lớp `MenuScreen`.

#include "Game.h"
// Bao gồm tệp tiêu đề `Game.h` để triển khai các phương thức của lớp `Game`.

using namespace sfSnake;
// Sử dụng namespace `sfSnake` để tránh phải viết lặp lại namespace khi sử dụng các thành phần trong trò chơi.

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);
// Hằng số `TimePerFrame` xác định thời gian cho mỗi khung hình (frame) là 0.1 giây (tương ứng với 10 FPS).

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();
// Khởi tạo con trỏ thông minh `Screen` trỏ tới một đối tượng `MenuScreen` (màn hình menu chính của trò chơi).

Game::Game()
	: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
	// Hàm khởi tạo của lớp `Game`, tạo cửa sổ trò chơi với kích thước `Width` x `Height` và tiêu đề "sfSnake".
{
	bgMusic_.openFromFile("canon.mp3");
	// Mở file âm thanh nền `canon.mp3`.

	bgMusic_.setLoop(true);
	// Đặt âm thanh phát lặp lại.

	bgMusic_.play();
	// Bắt đầu phát âm thanh nền.
}

void Game::handleInput()
// Phương thức xử lý các sự kiện đầu vào của trò chơi.
{
	sf::Event event;

	while (window_.pollEvent(event))
		// Lặp qua tất cả các sự kiện xảy ra trong cửa sổ.
	{
		if (event.type == sf::Event::Closed)
			window_.close();
		// Nếu sự kiện là đóng cửa sổ, đóng cửa sổ trò chơi.
	}

	Game::Screen->handleInput(window_);
	// Gọi phương thức `handleInput` của màn hình hiện tại (ví dụ, `MenuScreen` hoặc màn hình chơi game).
}

void Game::update(sf::Time delta)
// Phương thức cập nhật trạng thái trò chơi dựa trên thời gian `delta`.
{
	Game::Screen->update(delta);
	// Gọi phương thức `update` của màn hình hiện tại, truyền vào thời gian đã trôi qua.
}

void Game::render()
// Phương thức vẽ các đối tượng lên cửa sổ.
{
	window_.clear();
	// Xóa nội dung hiện tại của cửa sổ.

	Game::Screen->render(window_);
	// Gọi phương thức `render` của màn hình hiện tại, vẽ các đối tượng lên cửa sổ.

	window_.display();
	// Hiển thị nội dung đã được vẽ lên màn hình.
}

void Game::run()
// Phương thức chính của trò chơi, bắt đầu vòng lặp trò chơi.
{
	sf::Clock clock;
	// Khởi tạo đồng hồ để đo thời gian giữa các khung hình.

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	// Biến lưu thời gian đã trôi qua kể từ lần cập nhật trước.

	while (window_.isOpen())
		// Vòng lặp chính của trò chơi, chạy khi cửa sổ còn mở.
	{
		sf::Time delta = clock.restart();
		// Lấy thời gian trôi qua kể từ lần gọi `restart` trước đó và đặt lại đồng hồ.

		timeSinceLastUpdate += delta;
		// Cộng dồn thời gian trôi qua vào biến `timeSinceLastUpdate`.

		while (timeSinceLastUpdate > Game::TimePerFrame)
			// Nếu thời gian trôi qua vượt quá thời gian cho mỗi khung hình (TimePerFrame), thực hiện cập nhật.
		{
			timeSinceLastUpdate -= TimePerFrame;
			// Giảm thời gian trôi qua bằng thời gian của một khung hình.

			handleInput();
			// Xử lý các sự kiện đầu vào.

			update(TimePerFrame);
			// Cập nhật trạng thái trò chơi.
		}

		render();
		// Vẽ các đối tượng lên cửa sổ.
	}
}
