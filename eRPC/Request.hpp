#ifndef ERPC_REQUEST_HPP
#define ERPC_REQUEST_HPP

#include <string>
#include <vector>

namespace eRPC
{
  class Request
  {
  public:
    /**
     * Construct a request with the given message ID, method, and parameters.
     */
    Request(int msgid, std::string method, std::vector<std::string> params);

    /**
     * Construct a request by parsing the given message.
     */
    Request(std::string msg);

    /**
     * Serialize the request to a string.
     */
    std::string serialize();

    int getMsgid();
    std::string getMethod();
    std::vector<std::string> getParams();

  private:
    int msgid;
    std::string method;
    std::vector<std::string> params;
  };
}

#endif // ERPC_REQUEST_HPP