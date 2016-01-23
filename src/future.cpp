#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <boost/asio.hpp>

void asyncRun() {
    std::cout << "Async..." << std::flush;

    boost::asio::io_service io_service;
    std::shared_ptr < std::promise<int> > promise(new std::promise<int>());
    std::future<int> future = promise->get_future();

    io_service.post([promise]()
    {
        std::chrono::milliseconds dura( 2000 );
        std::this_thread::sleep_for( dura );
        promise->set_value(9);
    });

    std::thread t1([&io_service] {io_service.run();});
    t1.detach();

    std::cout << "Waiting..." << std::flush;
    future.wait();
    std::cout << "Done!\nResults are: " << future.get() << '\n';

}

void nonBlockingRun() {
    std::cout << "Non Blocking..." << std::flush;

    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    std::thread t1([](std::promise<int> p)
    {
        std::chrono::milliseconds dura( 2000 );
        std::this_thread::sleep_for( dura );
        p.set_value(9);
    }, std::move(promise));
    t1.detach();

    std::cout << "Waiting...\n" << std::flush;
    std::future_status status;
    do {
        status = future.wait_for(std::chrono::seconds(0));

        if (status == std::future_status::deferred) {
            std::cout << "+";
        } else if (status == std::future_status::timeout) {
            std::cout << ".";
        }
    } while (status != std::future_status::ready);
    std::cout << "Done!\nResults are: " << future.get() << '\n';
}

void blockingRun() {
    std::cout << "Blocking..." << std::flush;

    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    std::thread t1([](std::promise<int> p)
    {
        std::chrono::milliseconds dura( 2000 );
        std::this_thread::sleep_for( dura );
        p.set_value(9);
    }, std::move(promise));
    t1.detach();

    std::cout << "Waiting..." << std::flush;
    future.wait();
    std::cout << "Done!\nResults are: " << future.get() << '\n';
}

int main2() {
    nonBlockingRun();
    blockingRun();
    asyncRun();
}
