#include "Run.hpp"
#include "Config/Config.hpp"

int main(void)
{
	Config::Configure();

	Run app;
	return app.exec();

}
