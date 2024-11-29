#include "analyzer.h"

#include "drawing.h"
#include "shared.h"
#include <algorithm>
#include <fstream>
#include <ranges>

namespace views = std::views;
namespace ranges = std::ranges;

bool Dist2DAnalyzer::Load() {
  std::ifstream ifs(InFileName, std::ios::in | std::ios::binary);
  if (!ifs.is_open())
    return false;

  ifs.seekg(0, std::ios::end);
  mFile_Size = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  mData = std::vector<double>(mFile_Size / sizeof(double));

  if (!ifs.read(reinterpret_cast<char *>(mData.data()), mFile_Size)) {
    throw std::runtime_error("Error reading file");
  }

  return true;
}

bool Dist2DAnalyzer::Analyze() {
  for (auto const pair : mData | views::as_const | views::chunk(2)) {
    auto x = static_cast<size_t>((pair[0] - NumStart) / IntervalSizeX);
    auto y = static_cast<size_t>((pair[1] - NumStart) / IntervalSizeY);

    if (x >= ImgWidth || y >= ImgHeight)
      continue;

    auto index = x + y * ImgWidth;

    if (index >= Histogram.size())
      Histogram.resize(index + 1);

    Histogram[index]++;
  }

  mMaximum = ranges::max(Histogram);

  return true;
}

bool Dist2DAnalyzer::Save_Image(const std::string &out) {
  PPMDrawing draw;
  draw.Init(ImgWidth, ImgHeight, out);

  for (auto const [index, value] : Histogram | views::as_const |
                                       views::chunk(ImgWidth) | views::join |
                                       views::enumerate) {
    double factor =
        1.0 - (static_cast<double>(value) / static_cast<double>(mMaximum));

    auto grayscale = static_cast<uint8_t>(255.0 * factor);

    IDrawing::Color c{grayscale, grayscale, grayscale};

    auto x = static_cast<int>(index % ImgWidth);
    auto y = static_cast<int>(index / ImgWidth);
    draw.Draw_Pixel(x, y, c);
  }

  draw.Save();

  return true;
}
