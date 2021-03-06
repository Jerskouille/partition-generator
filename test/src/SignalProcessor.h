#ifndef SIGNAL_PROCESSOR_HH
#define SIGNAL_PROCESSOR_HH

// #include "SignalPrinter.h"
#include <vector>
#include "Misc.h"
#include <fftw3.h>

/*!
    \file SignalProcessor.h
    Contains all processing functions and algorithms of the input Signal.
*/

/*! \brief SignalProcessor class

    SignalProcessor is processing the signal gathered by #WavParser
    using multiple methods and algorithms specifically developped for pitch dectection.

    \date September 2014
*/

class SignalProcessor
{
    public:
    /*! Constructor.
        Sets the frequency, frenquency error, frequency lowbound and frequency highbound to 0.
        Instantiate its own #SignalPrinter.
    */
    	SignalProcessor();

    //! Destructor.
        ~SignalProcessor();

    /*! Initiates the signal printer #sPrinter and sets its parameters.
        \param lowbound The minimum value (in Hertz) from which the signal will be reprenseted on each graph.
        \param highbound The maximum value (in Hertz) until which the signal will be reprenseted on each graph.
        \param factor The factor to be multiplied to the index stored in each file so it can be converted into Hertz.
    */
        // void initPrinter(unsigned int lowbound, unsigned highbound, float factor);

    /*! Sets the paramaters necessary to calibrate the FFT algorithm.
        \param rate The rate to which the signal must be read. It is used to compute the size #window_size of each portions of signal
            that are then processed by the FFT one after an other until all the signal has been read.
        \param max_freq_error This is the maximum error we accept in the input frequency.
        \param window_size This variable is the effective size of the portion of the signal to be processed at a given time.
        \param window_ms_size This variable is the size (in milliseconds) of the shift between windows.
        \param signal_lentgh This variable is the length of the signal.
    */
        void setParams(int rate, float max_freq_error, int window_size, int window_ms_size, int signal_lentgh);


    /*! Set the array #fft to the data #data.
    */
        void setFFT(fftw_complex *data);

    /*! Set the size of the FFT buffer #fftBufferSize.
    */
        void setFFTSize(int size);

    /*! Returns the number of periods contained in the signal represented by #buff.
    */
        int computePeriod(float *buff);

    /*! Instantiates the different arrays meant to hold the different stages of the signals through its processing.
    */
        void fftInit();

    /*! Apply a hamming window to the given array in order to smooth the signal before the FFT.
        \param windowLength The length of the array to which the hamming window is applied.
        \param buffer The array to which the hamming window is applied.
    */
        void hamming(int windowLength, double *buffer);

    /*! Apply, before the FFT, a Blackman Harris window to the given array in order to reduce high-frequency noise in the signal.
        \param windowLength The length of the array to which the hamming window is applied.
        \param buffer The array to which the hamming window is applied.
    */
        void blackmanHarris(int windowLength, double *buffer);

    /*! Sets the frequency range between which the signal is to be processed.
        \param Represents the frequency from which we decide to process the signal.
                Before that the signal is set to 0 and not taken into account.
        \param Represents the frequency from which we decide to stop processing the signal.
                After that the signal is set to 0 and not taken into account.
    */
        void setFrequencyRange(unsigned int lowbound, unsigned int highbound);


    /*! Computes the #spectrum processed via the magnitude of the signal resulting from the microphone input.
    */
        void computeMicroSpectrum();

    /*! Computes the size of each window that are processed by the FFT, and the size of the resulting arrays.
    */
        void computeFFTSize();

    /*! Computes the #spectrum processed via the magnitude of the signal resulting from the microphone input.
    */
        float processMicroSignal2(float *buff);

    /*! The main signal processing function that takes signals from #left and #right audio canals of the wav file.
      * It devides the wav file in portions of #fftBufferSize and calls #STFT for each of them. 
    */
        void processSignal(float *left, float *right);


    /*! STFT is charged to apply the blackman-Harris window to the audio signal and apply the FFT to each of the wav segments. 
    */
    	  void STFT(float *left, float *right, fftw_plan *plan_forward_left, fftw_plan *plan_forward_right,
                          fftw_complex *fft_result_left, fftw_complex *fft_result_right,
                          double *dataWindowLeft, double *dataWindowRight, double *window, int *windowPosition, bool *bStop);

    /*! Computes the magnitude of the signal over the frequency range from the data resulting of the FFT #fftw_complex.
        If noise is given, it add the new magnitudes to #noiseMag.
    */
    	void computeMagnitude();
    	void computeMagnitude(bool noise);

    /*! Computes the spectrum of the signal from its magnitude array #fftMag.
    */
    	void computeSpectrum();

    /*! Computes the harmonic product spectrum from the #spectrum of the signal at the given order.
        \param harmonics The order to which the harmonic product spectrum must be computed.
    */
    	void computeHPS(int harmonics);


    /*! Add a note to the mmap notes for the onset detection.
        \param note The actual note in the American standard format to add.
        \param amp The famplitude of the note to add.

    */
        void addNote(std::string note, float amp);

    /*! Returns the different notes detected in one callback iteration (no OnSet filter).
    */
        std::vector<std::pair<std::string, float> > getNotes();

    /*! Returns the list #notes_tests containing all the notes detected in the reading of the wav file.
    */
        std::vector<std::pair<std::string, float> > getNotesTests();
      
    /*! Returns the list #OnSetNotes containing the newly played notes.
    */
        std::vector<std::string> getOnSetNotes();



    /*! Detect the biggest slope of the detected notes.
    */
        void
        detectBiggestSlope();

    /*! Detect the onset of a note.
    */
        void detectOnset(int depth, float threshold);

      /*! Returns the frequency of the fundamental resulting from the hps.
      */
        float getFundamental(bool *newNote);

    /*! Finds the fundamental frequency by finding the maximum of the #hps array.
    */
    	std::pair<float, float> findFundamental(int harmonics);

    /*! Returns #fftw_complex.
        \return fftw_complex 
    */
    	fftw_complex *getFFTComplex();


    /*! Returns the number of periods contained in the array passed in parameter.
    */
      int computeMicroPeriod(float *buff);

    /*! Returns #fft_size
        \return fft_size
    */
    	int getFFTSize();

    /*! Returns the signal printer #sPrinter
    * \return sPrinter 
    */
        // SignalPrinter getPrinter();

    public:


    /*! Returns the midi note corresponding to the note frequency
    * \param freq Frequency of the note in Hz
    * \return midiNote
    */
    int freqToMidi(float freq);

    	// attributes
	/**
	 * \var max_freq_error
	 * This is the maximum error we accept in the input frequency.
	 */
        float max_freq_error;

	/**
	 * \var fundamental
	 * This variable is the frequency of the fundamental detected in the file.
	 */
        float fundamental;

	/**
	 * \var fft_size
	 * This variable stores the size of the data once it has been processed by the fft.
	 */
        int fft_size;

    /**
     * \var rate
     * The rate to which the signal must be read. It is used to compute the size #window_size of each portions of signal
     * that are then processed by the FFT one after an other until all the signal has been read.
     */
        int rate;

    /**
     * \var window_ms_size
     * This variable is the size (in milliseconds) of the portion of the signal to be processed at a given time.
     */
        int window_ms_size;

    /**
     * \var shift_ms_size
     * This variable is the size (in milliseconds) of the shift between windows.
     */
        int shift_ms_size;

	/**
	 * \var window_size
	 * This variable is the effective size of the portion of the signal to be processed at a given time.
	 */
        int window_size;

	/**
	 * \var shift_size
	 * This variable is the effective size of the shift between windows.
	 */
        int shift_size;

	/**
	 * \var signal_lentgh
	 * This variable is the length of the signal.
	 */
        int signal_lentgh;

	/**
	 * \var fftBufferSize
	 * This variable stores the size of the data given to the fft.
	 */
        int fftBufferSize;

	/**
	 * \var lowbound
	 * This variable is the low bound frequency of the input.
     * It represents the frequency from which we decide to process the signal.
     * Before that the signal is set to 0 and not taken into account.
	 */
        unsigned int lowbound;

	/**
	 * \var highbound
	 * This variable is the high bound frequency of the input.
     * It represents the frequency from which we decide to stop processing the signal.
     * After that the signal is set to 0 and not taken into account.
	 */
        unsigned int highbound;

    /**
     * \var fftMag
     * The array containing the new representation of the signal (Magnitude over frequency) computed from #fftw_complex.
     */
        float *fftMag;

    /**
     * \var spectrum
     * The array containing the spectrum of the signal computed from #fftMag.
     */
        float *spectrum;

    /**
     * \var hps
     * The array cointaining the harmonic product spectrum of the signal computed from #spectrum.
     */
        float *hps;

    /**
     * \var firstAmp
     * The amplitude of the fundamental detected from the signal processing two iterations ago.
     */
       float firstAmp;
      
    /**
     * \var lastAmp;
     * The amplitude of the fundamental detected from the signal processing one iteration ago.
     */
        float lastAmp;
       
    /**
     * \var currAmp
     * The amplitude of the fundamental detected from the signal processing during this iteration.
     */
        float currAmp;
       
    /**
     * \var newNote
     * The boolean being checked to determine if the note fundamental frequency detected corresponds to a newly played not or just the result from the last note decaying.
     */
        bool *newNote;

    /**
     * \var noiseMag
     * The array containing the sum of all magnitudes of noise samples
     */
        float* noiseMag;

    /**
     * \var fft
     * The array containing the signal once it has been processed by the FFT.
     */
        fftw_complex *fft;

    /**
     * \var notes
     * The array containing the notes detected at every callback. It contains the actual note written in the American norm and the amplitude of the note.
     */
        std::vector<std::pair<std::string, float>> notes;
    
    /**
     * \var notes_tests
     * The array containing the notes detected at every iteration through the reading of the wav. It contains the actual note written in the American norm and the amplitude of the note.
     * This array is solely used for testing purposes.
     */
        std::vector<std::pair<std::string, float>> notes_tests;
    
    /**
     * \var onSetNotes
     * The array containing the notes detected at every callback after the OnSet filter. Each note in this list has been detected a new note and not the result from the last note decaying.
     */
        std::vector<std::string> onSetNotes;

    /**
     * \var sPrinter
     * The class built to store all the different stages of the signal and produce their associated graphs.
     */
        // SignalPrinter sPrinter;

    /**
     * \var m
     * The class is used to handle all sort of stuff.
     */
        Misc m;

    /**
     * \var midiForFreq 
     * Table saving all the correspondances from midi notes to the associated frequencies.
     */
        float midiForFreq[128];
};

#endif /* SIGNAL_PROCESSOR_HH */
