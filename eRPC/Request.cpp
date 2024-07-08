#include "Request.hpp"

#include <sstream>
#include <stdexcept>

namespace eRPC
{
  Request::Request(int msgid, std::string method, std::vector<std::string> params)
      : msgid(msgid), method(method), params(params)
  {
  }

  Request::Request(std::string msg) : msgid(-1), method(), params()
  {
    std::string line;
    std::istringstream iss(msg);

    std::getline(iss, line);
    if (line != "eRPC 1.0")
    {
      throw std::runtime_error("Invalid Request");
    }

    std::getline(iss, line);
    msgid = std::stoi(line);

    std::getline(iss, method);

    while (std::getline(iss, line))
    {
      params.push_back(line);
    }
  }

  std::string Request::serialize()
  {
    std::string msg = "eRPC 1.0\n";

    msg += std::to_string(msgid) + "\n";
    msg += method + "\n";

    for (std::string param : params)
    {
      msg += param + "\n";
    }
    msg.pop_back();

    return msg;
  }

  int Request::getMsgid()
  {
    return msgid;
  }

  std::string Request::getMethod()
  {
    return method;
  }

  std::vector<std::string> Request::getParams()
  {
    return params;
  }
}