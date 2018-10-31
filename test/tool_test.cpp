#include "tool_test.h"

tool_test::tool_test():m_tool()
{

}

tool_test::tool_test(const Tool temp){
    m_tool=temp;
}
tool_test::~tool_test();
//测试wps84ToGejTest()
void tool_test::WPS84Test(){
   double lat_test=m_tool.TransfromLatToDouble(30.5594483655-105.0, 103.9976232481 - 35.0);
   double lon_test=m_tool.TransfromLatToDouble(30.5594483655-105.0, 103.9976232481 - 35.0);
   QGeoCoordinate coordinate=m_tool.WPS84ToGcj02(30.5594483655,103.9976232481);
   qDebug()<<"--------This test start--------";
   qDebug()<<"This test lat is <<"<<lat_test;
   qDebug()<<"This test lon is <<"<<lon_test;
   qDebug()<<"This test coordinate is <<"<<coordinate.toString;
   qDebug()<<"--------This test end--------";

}
