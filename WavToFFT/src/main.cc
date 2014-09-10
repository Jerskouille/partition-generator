/* Start reading here */
#include <fftw3.h>
#include "SignalProcessor.h"
#include "WavParser.h"

#define NUM_COMMANDS 4


/* Resume reading here */
int main(int argc, char *argv[]) {

	WavParser *wp = new WavParser();
	SignalProcessor *sp = new SignalProcessor();

	wp = wp;
	sp = sp;

	return 0;

/*
	SNDFILE *sf;
    SF_INFO info;
    //int num_channels;
    int num, num_items;
    int *buf;
    int f,sr,c;
    int i,j;
    double *in;
    FILE *out;
    
    argc = argc;

     Open the WAV file.
    info.format = 0;
    sf = sf_open(argv[1],SFM_READ,&info);
   
    if (sf == NULL)
        {
        printf("Failed to open the file.\n");
        exit(-1);
        }
    Print some of the info, and figure out how much data to read.
    f = info.frames;
    sr = info.samplerate;
    c = info.channels;
   
    printf("frames=%d\n",f);
    printf("samplerate=%d\n",sr);
    printf("channels=%d\n",c);
   
    num_items = f*c;
   
    printf("num_items=%d\n",num_items);
   
    Allocate space for the data to be read, then read it.
    buf = (int *) malloc(num_items*sizeof(int));
    num = sf_read_int(sf,buf,num_items);
   
    sf_close(sf);
   
    printf("Read %d items\n",num);
   
    Write the data to filedata.out.
    out = fopen("log/filedata.out","w");
   	in = (double *)fftw_malloc ( sizeof ( double ) * num );
   	
    for (i = 0; i < num; i += c)
        {
        for (j = 0; j < c; ++j)
            fprintf(out,"%d ",buf[i+j]);
        	in[i + j] = buf[i+j];
        fprintf(out,"\n");
        }
    fclose(out);

	std::string commandsForGnuplot[] = {"set title \"DFT\"",
									"set xlabel \"Frequency (Hz)\"",
									"set ylabel \"Amplitude (dB)\"",
									"plot 'log/data.temp' with lines"};
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");

  	int nc = ( num / 2 ) + 1;

  	fftw_complex *result = reinterpret_cast<fftw_complex*>(fftw_malloc ( sizeof ( fftw_complex ) * nc ));

  	fftw_plan plan_forward = fftw_plan_dft_r2c_1d ( num, in, result, FFTW_ESTIMATE );
	fftw_execute ( plan_forward );

	fftw_plan plan = fftw_plan_dft_1d(NUM_POINTS,
		signal,
		result,
		FFTW_FORWARD,
		FFTW_ESTIMATE);

	acquire_from_somewhere(signal);
	fftw_execute(plan);
	do_something_with(result);

	do_something_with(result, nc);
    
    for (i=0; i < NUM_COMMANDS; i++) {
    	fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i].c_str()); //Send commands to gnuplot one by one.
    }

	fftw_destroy_plan(plan_forward);

*/

}