/*******************************************************************
 * Test App
 * You can haz GPL license.
 *
 *******************************************************************
 */

#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <memory>

#include <drwnBase.h>

#include <foobar1.h>

int main (int argc, char** argv) {

  std::unique_ptr<Foobar1> f(new Foobar1());

  DRWN_LOG_MESSAGE("hello world");

  f->printSelfHello();

  return 0;
}



