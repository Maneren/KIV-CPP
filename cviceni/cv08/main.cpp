#include <array>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <print>
#include <thread>

// Pro ted nereste, zda je v roure dost mista - to by nahravalo na implementaci
// semaforu a to ted nechceme (semafor - viz ZOS, PPR, UPP, ...)

class StupidPipe final {
public:
  StupidPipe() {
    //
  }

  void Write(char c) {
    std::lock_guard l(mMutex);

    mBuffer[mWrite_Cursor] = c;
    mWrite_Cursor = (mWrite_Cursor + 1) % mBuffer.size();

    mCond.notify_one();
  }

  char Read() {
    std::unique_lock l(mMutex);

    if (mRead_Cursor == mWrite_Cursor)
      mCond.wait(l, [this] { return mWrite_Cursor != mRead_Cursor; });

    char c = mBuffer[mRead_Cursor];
    mRead_Cursor = (mRead_Cursor + 1) % mBuffer.size();
    return c;
  }

private:
  std::array<char, 128> mBuffer;
  size_t mWrite_Cursor = 0;
  size_t mRead_Cursor = 0;
  mutable std::mutex mMutex;
  std::condition_variable mCond;
};

std::mutex stdout_mutex;

void Producent_Thread(StupidPipe &r, char c, size_t delay) {
  {
    std::lock_guard l(stdout_mutex);
    std::cout << "Startuje producent '" << c << "'" << std::endl;
  }

  while (true) {
    r.Write(c);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
}

void Konzument_Thread(StupidPipe &r, size_t delay) {
  {
    std::lock_guard l(stdout_mutex);
    std::cout << "Startuje konzument" << std::endl;
  }

  while (true) {
    char c = r.Read();

    {
      std::lock_guard l(stdout_mutex);
      std::cout << c << std::endl; // bez endl se dlouho bufferuje
    }
  }
}

int main() {
  StupidPipe roura;

  std::thread prod1(&Producent_Thread, std::ref(roura), 'a', 1500);
  std::thread prod2(&Producent_Thread, std::ref(roura), 'b', 1200);
  std::thread prod3(&Producent_Thread, std::ref(roura), 'c', 2300);

  std::thread konz(&Konzument_Thread, std::ref(roura), 300);

  prod1.join();
  prod2.join();
  prod3.join();
  konz.join();

  return 0;
}
