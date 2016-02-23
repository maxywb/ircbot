
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class HttpFetch {
public:

    virtual ~HttpFetch( ) {

    }

    virtual std::string getUrlAsString( const std::string &url ) const {
        return std::string("foo" );
    }
};

class HtmlParser {
public:

    HtmlParser( const HttpFetch &http ) : m_http( http ) {

    }

    std::vector<std::string> getAllLinks( const std::string &url ) const {
        return std::vector<std::string>();
    }

private:
    HttpFetch m_http;
};
	 
class MultiplyTest : public ::testing::Test {
 protected:
  int something;

  virtual void SetUp() {
    something = 12;
  }
	 
  virtual void TearDown() {
    
  }
};
	 
TEST_F(MultiplyTest, twoValues){
  const int x = 4;
  const int y = 5;

  EXPECT_EQ(6,2*3);
}


using ::testing::Return;

class HttpFetchMock : public HttpFetch {
public:
    MOCK_CONST_METHOD1( getUrlAsString, std::string( const std::string& ) );
};

TEST(HtmlParser, NoData) {
    char *html;
    HttpFetchMock mock;
    HtmlParser parser(mock);

    EXPECT_CALL(mock, getUrlAsString("http://example.net"))
        .WillOnce(Return(std::string(html)));

    std::vector<std::string> links = parser.getAllLinks("http://example.net");
    EXPECT_EQ(0, links.size());

    mock.getUrlAsString("http://example.net");

}

int main( int argc, char *argv[] ) {
    ::testing::InitGoogleMock( &argc, argv );
    return RUN_ALL_TESTS( );
}
