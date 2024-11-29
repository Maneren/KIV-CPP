#pragma once

#include <string>
#include <vector>

class IAnalyzer {
public:
  virtual ~IAnalyzer() = default;

  virtual bool Load() = 0;

  virtual bool Analyze() = 0;

  virtual bool Save_Image(const std::string &out) = 0;

  virtual size_t Get_File_Size() const = 0;
};

class DummyAnalyzer : public IAnalyzer {
public:
  DummyAnalyzer() = default;
  ~DummyAnalyzer() override = default;

  bool Load() override { return true; }

  bool Analyze() override { return true; }

  bool Save_Image(const std::string &) override { return true; }

  size_t Get_File_Size() const override { return 0; }
};

class Dist2DAnalyzer : public IAnalyzer {
private:
  std::vector<size_t> Histogram;

  std::vector<double> mData;

  size_t mFile_Size = 0;

  size_t mMaximum = 0;

public:
  Dist2DAnalyzer() = default;
  ~Dist2DAnalyzer() override = default;

  bool Load() override;

  bool Analyze() override;

  bool Save_Image(const std::string &out) override;

  size_t Get_File_Size() const override { return mFile_Size; }
};
