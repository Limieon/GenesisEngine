#pragma once

extern ge::client::Application* createApplication();

int main(int argc, char** argv) {
	auto app = ge::client::createApplication();
	app->run();
	delete app;
}
