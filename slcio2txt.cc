#include "lcio.h"
#include "EVENT/LCCollection.h"
#include "UTIL/BitField64.h"
#include "IMPL/LCCollectionVec.h"
#include "IMPL/LCEventImpl.h"
#include "IMPL/LCParametersImpl.h"
#include "IMPL/LCRunHeaderImpl.h"
#include "IMPL/LCFlagImpl.h"
#include "UTIL/LCTime.h"
#include "UTIL/LCTOOLS.h"
#include "IMPL/LCGenericObjectImpl.h"
#include <UTIL/BitField64.h>
#include <algorithm>
#include <functional>

#include <sstream>
#include <string>
#include <map>
#include <utility>

using namespace std ;
using namespace lcio ;

void slcio2txt(){

LCReader* lcReader = LCFactory::getInstance()->createLCReader() ;//create an instance of LCReader using LCFactory:
int nEvents = 0;
//double IC_const = 0;

try{

    lcReader->open( "/nfs/dust/ilc/user/opinto/condDB_Intercalibration_ahc2_Intercalibration_190109_20190521_140315.slcio" ) ;
    //cout << "Slcio file is opened" <<endl;

    //cout <<"Running event loop"<<endl;
    LCEvent*  evt;
    while( (evt = lcReader->readNextEvent()) != 0 ) {
    //LCTOOLS::dumpEvent( evt ) ;

    LCCollection* Intercalibration = evt->getCollection("Intercalibration") ;
    auto cellIdString = Intercalibration->getParameters().getStringVal("ModuleEncodingString") ;
    //cout <<"Got the collection name "<<endl;
    int nRawData = Intercalibration->getNumberOfElements() ;
    //cout  << " looping over the elements of the generic objects" << endl;
    //nRawData = 5;
    BitField64 bf (cellIdString) ;

    for(int j=0;j<nRawData;j++)
      {
        //=========== using the class LCGenericObjectImpl================//
        LCGenericObjectImpl* IC_const = dynamic_cast <LCGenericObjectImpl*> ( Intercalibration->getElementAt(j) ) ;// use dynamic cast to convert Base pointer into Derived pointer
        //=================checking if the variable types are int or float or double================//
        //int nInt    = IC_const->getNInt();
        //int nFloat  = IC_const->getNFloat();
        //int nDouble = IC_const->getNDouble();
        //cout << nInt << " " << nFloat << " " << nDouble << endl;
        //cout << IC_const->getIntVal(0) << " " << IC_const->getDoubleVal(0) << endl; //" " << IC_const->getDoubleVal(1) << " " << IC_const->getDoubleVal(2) << " " << IC_const->getDoubleVal(3) << " " << endl;

        int cellid = IC_const->getIntVal(0); //Getting value from the first column
        bf.setValue(cellid);
        int module2 = bf["module"]; // 2^6 -1 and it is 6 bit long
        int chip2 = bf["chip"]; // 2^10 -1 and bit shift by 6 and consider only 4 remaining
        int channel2 = bf["channel"]; // 2^16 -1 and shift by 10 and consider only 6 remaining
        cout << module2 << " " << chip2 << " " << channel2 << " " << IC_const->getDoubleVal(0)<<endl;
         //module:0:6,chip:6:4,channel:10:6,
         //=============================Process of doing bit field==================================//
         /*int module = cellid & 63; // 2^6 -1 and it is 6 bit long
         int chip = (cellid & 1023 ) >> 6; // 2^10 -1 and bit shift by 6 and consider only 4 remaining
         int channel = (cellid & 65535) >> 10; // 2^16 -1 and shift by 10 and consider only 6 remaining
         cout << module << " " << chip << " " << channel << " " << IC_const->getDoubleVal(0)<<endl;*/
      }
    nEvents ++ ;
  }

    lcReader->close() ;
  }
  catch(IOException& e){

    cout << " Unable to read and analyze the LCIO file - " << e.what() << endl ;
  }
}
int main()
{
  slcio2txt();
}
