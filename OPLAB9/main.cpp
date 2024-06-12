#include "parser_class.h"
#include "request_class.h"
#include "curl_request.h"

int main(int argc, char *argv[]) {
  // Example args:
  // --Vname=TRY --Vnom=7 --Filename=out.txt --DateDate=17.04.2024-20.04.2024 (recent week)
  // --Vname=EUR --Vnom=1 --Date=12.11.2005 (my birthday date actually)
  // --Vname=USD --Vnom=1 --DateDate=31.07.1998-09.09.1998 (default in 1998 in Russia)
  // --Vname=USD --Vnom=1 --Date=15.09.1993 (fall of a RUB currency)
  SetConsoleOutputCP(CP_UTF8);
  ParseArguments Parser;
  Parser.Parse(argc, argv);
  Request Req(Parser);
  GetCurlRequest(Parser, Req);
  return 0;
}
