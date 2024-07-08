#include "Response.hpp"

#include <sstream>

namespace eRPC
{
  Response::Response(int msgid, bool ok, std::string result)
      : msgid(msgid), ok(ok), result(result)
  {
  }

  Response::Response(std::string msg) : msgid(-1), ok(false), result()
  {
    std::string line;
    std::istringstream iss(msg);

    std::getline(iss, line);
    if (line != "eRPC 1.0")
    {
      throw std::runtime_error("Invalid Response");
    }

    std::getline(iss, line);
    msgid = std::stoi(line);

    std::getline(iss, line);
    ok = (line == "OK");

    std::getline(iss, result);
  }

  std::string Response::serialize()
  {
    std::string msg = "eRPC 1.0\n";

    msg += std::to_string(msgid) + "\n";
    msg += ok ? "OK\n" : "ERROR\n";
    msg += result;

    return msg;
  }

  int Response::getMsgid()
  {
    return msgid;
  }

  bool Response::isOk()
  {
    return ok;
  }

  std::string Response::getResult()
  {
    return result;
  }
}