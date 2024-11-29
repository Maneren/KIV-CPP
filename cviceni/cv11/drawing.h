#pragma once

#include <cstdint>
#include <string>
#include <vector>

class IDrawing {
public:
  struct Color {
    Color() : r(0), g(0), b(0) {};
    Color(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b) {};
    Color(const Color &c) = default;
    Color &operator=(const Color &c) = default;

    uint8_t r, g, b;
  };

  virtual ~IDrawing() = default;

  virtual void Init(int width, int height,
                    const std::string &filename = "image") = 0;
  virtual void Draw_Pixel(int x, int y, Color clr) = 0;
  virtual void Save() = 0;
};

class PPMDrawing : public IDrawing {
private:
  std::vector<Color> mBitmap;
  std::string mFilename;
  int mWidth, mHeight;

public:
  void Init(int width, int height,
            const std::string &filename = "image") override;
  void Draw_Pixel(int x, int y, Color clr) override;
  void Save() override;
};
