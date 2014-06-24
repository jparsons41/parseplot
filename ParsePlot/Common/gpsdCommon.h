#ifndef GPSD_COMMON_H
#define GPSD_COMMON_H

// these need to be shared with other apps
#define SHARED_MEM_PAGE_SIZE 4096
#define GPS_SHARED_MEM_PATH "/tmp"
#define GPS_SHARED_MEM_ID ('G')
#define GPS_SHARED_MEM_MUTEX "gpsd-mutex"

#define STRUCTURE_COPY_OFFSET 512

#define GPS_UPDATE_INTERVAL 10000

// size is 128 bytes
struct gpsData
{
   char spare1[176];
	char UTC[16];
	char fix[4];
	char lat[16];
	char latHemi[4];
	char lon[16];
	char lonHemi[4];
	char speed[16];
   char heading[16];
	char MSL[16];
	char date[16];
	char numSat[4];
   char GPSpitch[4];
   char GPSroll[4];
   char GPSheadingType[4];
   char Temperature[8];
};

/********************************************************* 
// An example of the shared memory string at location 0 (zero).

300112,114435.064,V,2836.012128,N,03429.940468,W,0.000,0.00,-24.031,6

// Here are the field descriptions

1 date 			DDMMYY
2 time 			HHMMSS.MS  in UTC timezone
3 fix			A is valid, V is invalid
4 lat			latitude
5 lat hemi		N or S
6 long			longitude
7 long hemi		W or E
8 speed			in knots
9 bearing		degrees
10 altitude		meters above sea level
11 satellites		number in use, not in view
12 

// The string at location is NULL terminated. There is no \r or \n.


// An application should do some setup like this

int shmid = shmget(key, SHARED_MEM_PAGE_SIZE, IPC_CREAT | 0600);
char *sharedMem = (char *)shmat(shmid, NULL, 0);
sem_t *mutex = sem_open(GPS_SHARED_MEM_MUTEX, O_CREAT, 0600, 1);


// Then you could read the string at location zero like this

if (!sem_wait(mutex)) {
	strcpy(str, sharedMem);
	sem_post(mutex);
}


// Starting at memory location STRUCTURE_COPY_OFFSET the data is repeated.
// This time it is a direct copy of the struct gpsData above.

// An application reading this data could do the following after
// performing the same setup for sharedMem and mutex.

struct gpsData data;

if (!sem_wait(mutex)) {
	memcpy(&data, sharedMem + STRUCTURE_COPY_OFFSET, sizeof(struct gpsData));
	sem_post(mutex);
}

************************************************************/

#endif // GPSD_COMMON_H

