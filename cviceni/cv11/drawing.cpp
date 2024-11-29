#include "drawing.h"

#include <algorithm>

void PPMDrawing::Init(int width, int height, const std::string &filename) {
  mFilename = filename;

  mBitmap.resize(width * height);
  std::ranges::fill(mBitmap, Color{255, 255, 255});
  mWidth = width;
  mHeight = height;
}

void PPMDrawing::Save() {
  std::ofstream ofs(mFilename + ".ppm", std::ios::out | std::ios::binary);

  ofs << "P6" << std::endl;
  ofs << mWidth << " " << mHeight << std::endl;
  ofs << "255" << std::endl;

  ofs.write(reinterpret_cast<const char *>(mBitmap.data()),
            mBitmap.size() * sizeof(Color));
}

void PPMDrawing::Draw_Pixel(int x, int y, Color clr) {
  if (y < 0 || y >= mWidth)
    return;

  if (x < 0 || x >= mHeight)
    return;

  mBitmap[y * mWidth + x] = clr;

  Save();
}
