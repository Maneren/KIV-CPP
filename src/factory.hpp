#pragma once
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

template <typename Interface, typename Args> class Factory {
public:
  using MaybeUniquePtr = std::optional<std::unique_ptr<Interface>>;
  using CreateFn = std::function<MaybeUniquePtr(const Args &args)>;

  /// Register a new type of the given Interface with a string name
  void register_type(const std::string &type, const CreateFn &fn) {
    creators[type] = fn;
  }

  /// Create a new instance of the given Interface based on the string name
  MaybeUniquePtr create(const std::string &type, const Args &args) const {
    auto it = creators.find(type);
    return it != creators.end() ? it->second(args) : std::nullopt;
  }

private:
  std::unordered_map<std::string, CreateFn> creators;
};
