#ifndef ERPC_RESPONSE_HPP
#define ERPC_RESPONSE_HPP

#include <string>

namespace eRPC
{
  class Response
  {
  public:
    /**
     * Construct a response with the given message ID, status, and result.
     */
    Response(int msgid, bool ok, std::string result);

    /**
     * Construct a response by parsing the given message.
     */
    Response(std::string msg);

    /**
     * Serialize the response to a string.
     */
    std::string serialize();

    int getMsgid();
    bool isOk();
    std::string getResult();

  private:
    int msgid;
    bool ok;
    std::string result;
  };
}

#endif // ERPC_RESPONSE_HPP