#ifndef FFBSS_H
#define FFBSS_H

#include "FireFlyDefs.h"
#include "../util/CircularQueue.h"
#include "util/FireFlyMessageOperators.h"
#include <QObject>

#define NANOSECONDS_PER_SEC 1000000000

using namespace firefly;

void timestampToSecUsec(quint64 timestamp, quint32 *secs, quint32 *usecs);
int countCaller(void);
void ffbssProc(const FIREFLY_BLOCK *ffbssBlock);



double hour(quint64 LastTimeStamp);

class ffbss : public QObject
{
   Q_OBJECT
   
    public:
        ffbss();

        ~ffbss();

        void processData(const FIREFLY_BLOCK *block);
        void reportData(const FIREFLY_BLOCK *ffbssBlock, long reportType, long reportCount);
        void filterGPS( const FIREFLY_BLOCK *block );
        double hour(quint32 LastTimestamp);
        double minute(quint32 LastTimestamp);
        double second(quint32 LastTimestamp);
        void getINI();
        void setAirTemp( double temp ) { m_airTemp = temp; }
        float filteredHeading(){ return m_filteredHeading; }
        double filteredLatitude(){ return m_filteredLatitude; }
        double filteredLongitude(){ return m_filteredLongitude; }
        bool airborne() { return m_airborne; }
        void setAcousticType(bool acoustic_type ) { m_airborne = acoustic_type; }
        
	void reopenDataFile(void);

    protected:

        struct Sample
        {
            QDateTime timestamp;
            double acoustic1;
            double acoustic2;
            double acoustic3;
            double acoustic4;
            double acoustic5;
            double acoustic6;
        }; // end struct Sample



      int bss_eventCount;
      uint32_t m_numSamples;

      typedef CircularQueue< Sample > Queue;
      Queue m_queue;
      int lastHeartbeat;
      double m_airTemp;
      uint16_t m_sysID;
      long m_counter;
      bool m_filterPositionValid;
      bool m_filterHeadingValid;
      long m_noGpsFixCounter;
      float m_filteredHeading;
      double m_filteredLatitude;
      double m_filteredLongitude;
      bool m_airborne;


private:
      //  QSettings *m_settings;

//int callCount;

   signals:
      void sig_message( const QByteArray& );
      void sig_detect( AirborneAcousticDetect& );
   
};
#endif // FFBSS_H

