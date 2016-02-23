
#include <string>

#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "OperationManager.hpp"
#include "Operation.hpp"
#include "IrcConnectorInterface.hpp"

class OperationManagerTest : public testing::Test {
 protected:
  virtual void SetUp() {

  }
	 
  virtual void TearDown() {
    
  }
};
	 
class IrcConnectorMock : public ircbot::IrcConnectorInterface {
 public:
  MOCK_METHOD2( connect, void(std::string const, size_t const));
  MOCK_METHOD1( join, void(std::string const &));
  MOCK_METHOD1( nick, void(std::string const &));
  MOCK_METHOD2( privmsg, void(std::string const &, std::string const &));
  MOCK_METHOD1( user, void(std::string const &));
  MOCK_METHOD0( read, std::string());
  MOCK_METHOD1( pong, void(std::string const &));
  MOCK_METHOD0( quit, void());
};

class OperationMock : public ircbot::Operation {
 public:
  OperationMock(boost::shared_ptr<ircbot::IrcConnectorInterface> ircConnection)
      : Operation(ircConnection)
  {}

  MOCK_METHOD1(consume, void(std::string const));

};

TEST(HtmlParser, NoData) {

  IrcConnectorMock m;

  boost::shared_ptr<ircbot::IrcConnectorInterface> mockConnector = boost::make_shared<IrcConnectorMock>();

  boost::shared_ptr<ircbot::Operation> mockOperation = boost::make_shared<OperationMock>(mockConnector);

  ircbot::OperationManager operationManager(mockConnector);

#if 0
  HtmlParser parser(mock);

  EXPECT_CALL(mock, getUrlAsString("http://example.net"))
      .WillOnce(testing::Return(std::string(html)));

  std::vector<std::string> links = parser.getAllLinks("http://example.net");
  EXPECT_EQ(0, links.size());

  mock.getUrlAsString("http://example.net");
#endif
}

int main( int argc, char *argv[] ) {
  testing::InitGoogleMock( &argc, argv );
  return RUN_ALL_TESTS( );
}
