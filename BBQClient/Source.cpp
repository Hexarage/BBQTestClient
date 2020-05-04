
#include <asio.hpp>
#include <iostream>
#include <string>
#include <boost/system/system_error.hpp>

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Expected 2 arguments." << std::endl;
			return 1; // Since we didn't really get what we expected, just abort execution
		}

		asio::io_context ioContext;

		asio::ip::tcp::resolver resolver(ioContext);
		asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "");	// Not really safe to just feed the argument without error checking TODO: Add error checking

		asio::ip::tcp::socket socket(ioContext);
		asio::connect(socket, endpoints);

		while (true)
		{
			std::string messageBuffer;
			asio::error_code error;

			size_t length = socket.read_some(asio::buffer(messageBuffer), error);

			if (error == asio::error::eof)
			{
				break; // connection severed
			}
			else if (error)
			{

			}

			std::cout << messageBuffer << std::endl;
		}



		//asio::io_service ioService;
		//asio::ip::tcp::resolver resolverObject(ioService);
		//asio::ip::tcp::resolver::query query(argv[1], "BBQClient");							// Not really safe to just feed the argument without error checking TODO: Add error checking
		//asio::ip::tcp::resolver::iterator endpointIterator = resolverObject.resolve(query);	// The list of endpoints is returned as an asio iterator
		//asio::ip::tcp::resolver::iterator end;												// Default construction should be sufficient as an end point according to docs
		//asio::ip::tcp::socket socket(ioService);
		//std::error_code error = asio::error::host_not_found;
		//while (error && endpointIterator != end)
		//{
		//	socket.close();
		//	socket.connect(*endpointIterator++, error);
		//}
		//if (error)
		//{
		//	//throw boost::system::system_error TODO: Figure out how to get this into the project through vcpkg
		//}

		//while (true)
		//{
		//	std::error_code error;
		//	std::string stringBuffer;
		//	size_t length = socket.read_some(asio::buffer(stringBuffer), error);

		//	if (error == asio::error::eof)
		//	{
		//		break; // The connection was closed cleanly by server
		//	}
		//	else if (error)
		//	{
		//		// throw boost::system::system error TODO: same as above
		//	}

		//	// TODO: message handling
		//}

	}
	catch (std::exception& e)
	{
		std::cerr << "Unexpected error: " << e.what() << std::endl;
	}
	system("pause");
	return 0;
}