#include <libkern/OSAtomic.h>
#include <CoreAudio/CoreAudio.h>
#include <AudioToolbox/AudioFormat.h>
#include <AudioToolbox/AudioConverter.h>
#include <AudioUnit/AudioUnit.h>
#include <AudioToolbox/AudioToolbox.h>
#include <CoreFoundation/CFByteOrder.h>


void UsageString(int exitCode)
{
	printf ("Usage: PlayFile /path/to/file\n");
	exit(exitCode);
}


#if 0
inline AudioComponent AudioComponentFindNext(AudioComponent ac, const AudioComponentDescription *desc)
{
    return FindNextComponent(ac, desc);
}

extern OSStatus
AudioCodecInitialize(   AudioCodec                                                                              inCodec,
                                                const AudioStreamBasicDescription* __nullable   inInputFormat,
                                                const AudioStreamBasicDescription* __nullable   inOutputFormat,
                                                const void*     __nullable                                                      inMagicCookie,
                                                UInt32                                                                                  inMagicCookieByteSize)
                                                                                                                                                __OSX_AVAILABLE_STARTING(__MAC_10_2,__IPHONE_2_0);



static HRESULT ca_get_audiodesc(AudioStreamBasicDescription *desc,
        const WAVEFORMATEX *fmt)
{
    const WAVEFORMATEXTENSIBLE *fmtex = (const WAVEFORMATEXTENSIBLE *)fmt;

    desc->mFormatFlags = 0;

    if(fmt->wFormatTag == WAVE_FORMAT_PCM ||
            (fmt->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
             IsEqualGUID(&fmtex->SubFormat, &KSDATAFORMAT_SUBTYPE_PCM))){
        desc->mFormatID = kAudioFormatLinearPCM;
        if(fmt->wBitsPerSample > 8)
            desc->mFormatFlags = kAudioFormatFlagIsSignedInteger;
    }else if(fmt->wFormatTag == WAVE_FORMAT_IEEE_FLOAT ||
            (fmt->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
             IsEqualGUID(&fmtex->SubFormat, &KSDATAFORMAT_SUBTYPE_IEEE_FLOAT))){
        desc->mFormatID = kAudioFormatLinearPCM;
        desc->mFormatFlags = kAudioFormatFlagIsFloat;
    }else if(fmt->wFormatTag == WAVE_FORMAT_MULAW ||
            (fmt->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
             IsEqualGUID(&fmtex->SubFormat, &KSDATAFORMAT_SUBTYPE_MULAW))){
        desc->mFormatID = kAudioFormatULaw;
    }else if(fmt->wFormatTag == WAVE_FORMAT_ALAW ||
            (fmt->wFormatTag == WAVE_FORMAT_EXTENSIBLE &&
             IsEqualGUID(&fmtex->SubFormat, &KSDATAFORMAT_SUBTYPE_ALAW))){
        desc->mFormatID = kAudioFormatALaw;
    }else
        return AUDCLNT_E_UNSUPPORTED_FORMAT;

    desc->mSampleRate = fmt->nSamplesPerSec;
    desc->mBytesPerPacket = fmt->nBlockAlign;
    desc->mFramesPerPacket = 1;
    desc->mBytesPerFrame = fmt->nBlockAlign;
    desc->mChannelsPerFrame = fmt->nChannels;
    desc->mBitsPerChannel = fmt->wBitsPerSample;
    desc->mReserved = 0;

    return S_OK;
}





 inline OSStatus AudioComponentInstanceNew(AudioComponent ac, AudioComponentInstance *aci)
{
    return OpenAComponent(ac, aci);
}

 inline OSStatus AudioComponentInstanceDispose(AudioComponentInstance aci)
{
    return CloseComponent(aci);
}

#endif

static int osstatus_to_hresult(OSStatus sc)
{
    switch(sc){
    case kAudioFormatUnsupportedDataFormatError:
    case kAudioFormatUnknownFormatError:
    case kAudioDeviceUnsupportedFormatError:
        return -1;
    case kAudioHardwareBadDeviceError:
        return -1;
    }
    return -1;
}


double PrepareFileAU (AudioUnit au, AudioStreamBasicDescription fileFormat, AudioFileID audioFile)
{    

    // calculate the duration
    UInt64 nPackets;
    UInt32 propsize = sizeof(nPackets);
        
    Float64 fileDuration = (nPackets * fileFormat.mFramesPerPacket) / fileFormat.mSampleRate;

    ScheduledAudioFileRegion rgn;
    memset (&rgn.mTimeStamp, 0, sizeof(rgn.mTimeStamp));
    rgn.mTimeStamp.mFlags = kAudioTimeStampSampleTimeValid;
    rgn.mTimeStamp.mSampleTime = 0;
    rgn.mCompletionProc = NULL;
    rgn.mCompletionProcUserData = NULL;
    rgn.mAudioFile = audioFile;
    rgn.mLoopCount = 1;
    rgn.mStartFrame = 0;
    rgn.mFramesToPlay = (nPackets * fileFormat.mFramesPerPacket);
            
    // prime the fp AU with default values
    unsigned int defaultVal = 0;

    // tell the fp AU when to start playing (this ts is in the AU's render time stamps; -1 means next render cycle)
    AudioTimeStamp startTime;
    memset (&startTime, 0, sizeof(startTime));
    startTime.mFlags = kAudioTimeStampSampleTimeValid;
    startTime.mSampleTime = -1;

    return fileDuration;
}

int AudioUnit_SetVolume(AudioUnit au, float left, float right)
{
    OSStatus err = noErr;
    static int once;

    //if (!once++) FIXME("independent left/right volume not implemented (%f, %f)\n", left, right);

    err = AudioUnitSetParameter(au, kHALOutputParam_Volume, kAudioUnitParameterFlag_Output, 0, left, 0);

    if (err != noErr)
    {
        //ERR("AudioUnitSetParameter return an error %s\n", wine_dbgstr_fourcc(err));
        return 0;
    }
    return 1;
}

int AudioUnit_GetVolume(AudioUnit au, float *left, float *right)
{
    OSStatus err = noErr;
    static int once;

//    if (!once++) FIXME("independent left/right volume not implemented\n");

    err = AudioUnitGetParameter(au, kHALOutputParam_Volume, kAudioUnitParameterFlag_Output, 0, left);
    if (err != noErr)
    {
        //ERR("AudioUnitGetParameter return an error %s\n", wine_dbgstr_fourcc(err));
        return 0;
    }
    *right = *left;
    return 1;
}

#if 0
const AudioStreamBasicDescription       CAStreamBasicDescription_sEmpty = { 0.0, 0, 0, 0, 0, 0, 0, 0, 0 };
CAStreamBasicDescription_CAStreamBasicDescription()
{
        memset (this, 0, sizeof(AudioStreamBasicDescription));
}

CAStreamBasicDescription_CAStreamBasicDescription(const AudioStreamBasicDescription &desc)
{
        SetFrom(desc);
}
#endif

OSStatus Open_AudioUnit (const AudioComponent inComp, AudioUnit outUnit)
{
    outUnit = inComp; 
    return noErr;
	
}

#if 0
/* place data from cap_buffer into provided AudioBufferList */
static OSStatus feed_cb(AudioConverterRef converter, UInt32 *nframes, AudioBufferList *data,
        AudioStreamPacketDescription **packets, void *user)
{
    ACImpl *This = user;

    *nframes = min(*nframes, This->cap_held_frames);
    if(!*nframes){
        data->mBuffers[0].mData = NULL;
        data->mBuffers[0].mDataByteSize = 0;
        data->mBuffers[0].mNumberChannels = This->fmt->nChannels;
        return noErr;
    }

    data->mBuffers[0].mDataByteSize = *nframes * This->fmt->nBlockAlign;
    data->mBuffers[0].mNumberChannels = This->fmt->nChannels;

    if(This->cap_offs_frames + *nframes > This->cap_bufsize_frames){
        UINT32 chunk_frames = This->cap_bufsize_frames - This->cap_offs_frames;

        if(This->wrap_bufsize_frames < *nframes){
            free(This->wrap_buffer);
            This->wrap_buffer = malloc(data->mBuffers[0].mDataByteSize);
            This->wrap_bufsize_frames = *nframes;
        }

        memcpy(This->wrap_buffer, This->cap_buffer + This->cap_offs_frames * This->fmt->nBlockAlign,
                chunk_frames * This->fmt->nBlockAlign);
        memcpy(This->wrap_buffer + chunk_frames * This->fmt->nBlockAlign, This->cap_buffer,
                (*nframes - chunk_frames) * This->fmt->nBlockAlign);

        data->mBuffers[0].mData = This->wrap_buffer;
    }else
        data->mBuffers[0].mData = This->cap_buffer + This->cap_offs_frames * This->fmt->nBlockAlign;

    This->cap_offs_frames += *nframes;
    This->cap_offs_frames %= This->cap_bufsize_frames;
    This->cap_held_frames -= *nframes;

    if(packets)
        *packets = NULL;

    return noErr;
}
#endif


void MakeSimpleGraph (AUGraph theGraph, AudioUnit fileAU, AudioStreamBasicDescription fileFormat, AudioFileID audioFile)
{    
    AudioComponentInstance unit;
    AudioComponentDescription desc;
    AudioComponent comp;
    OSStatus sc;

    memset(&desc, 0, sizeof(desc));

    // output node
    desc.componentType = kAudioUnitType_Output;
    desc.componentSubType = kAudioUnitSubType_DefaultOutput;
    desc.componentManufacturer = kAudioUnitManufacturer_Apple;

    if(!(comp = AudioComponentFindNext(NULL, &desc))){
        printf("AudioComponentFindNext failed\n");
        //return NULL;
    }

    sc = AudioComponentInstanceNew(comp, &unit);
    if(sc != noErr){
        printf("AudioComponentInstanceNew failed: %x\n", (int)sc);
        //return NULL;
    }


    AUNode outputNode;
    
    // file AU node
    AUNode fileNode;
    desc.componentType = kAudioUnitType_Generator;
    desc.componentSubType = kAudioUnitSubType_AudioFilePlayer;
        

    // install overload listener to detect when something is wrong
    AudioUnit anAU;
    
    fileAU = Open_AudioUnit (fileNode, anAU);
    
    // workaround a race condition in the file player AU
    usleep (10 * 1000);

#if 0
        /* if we have a surround file, then we should try to tell the output AU what the order of the channels will be */
// We can't even do right or left properly yet...
    if (fileFormat.NumberChannels() > 2) {
        unsigned int layoutSize = 0;
        OSStatus err;
        
        if (!err && layoutSize) {
            char* layout = new char[layoutSize];
            
            err = AudioFileGetProperty(audioFile, kAudioFilePropertyChannelLayout, &layoutSize, layout);
                                
            err = AudioUnitSetProperty (anAU, kAudioUnitProperty_AudioChannelLayout, 
                            kAudioUnitScope_Input, 0, layout, layoutSize);
            
            
            //delete [] layout;
        }
    }
#endif
}


int main (int argc, char * const argv[]) 
{
    if (argc < 2) UsageString(1);

    AudioFileID audioFile;
    
    const char* inputFile = argv[1];

    CFURLRef theURL = CFURLCreateFromFileSystemRepresentation(kCFAllocatorDefault, (UInt8*)inputFile, strlen(inputFile), false);
          
        OSStatus err = AudioFileOpenURL (theURL, kAudioFileReadPermission, 0, &audioFile);
        CFRelease(theURL);
            
    // get the number of channels of the file
    AudioStreamBasicDescription fileFormat;
    unsigned int propsize = sizeof(fileFormat);

    printf ("playing file: %s\n", inputFile);
    //printf ("format: "); fileFormat();

        // lets set up our playing state now
    AUGraph theGraph;
    AudioUnit fileAU;

        // this makes the graph, the file AU and sets it all up for playing
    MakeSimpleGraph (theGraph, fileAU, fileFormat, audioFile);
        

        // now we load the file contents up for playback before we start playing
        // this has to be done the AU is initialized and anytime it is reset or uninitialized
    Float64 fileDuration = PrepareFileAU (fileAU, fileFormat, audioFile);
        printf ("file duration: %f secs\n", fileDuration);


        // start playing    
        // sleep until the file is finished
        
    usleep ((int)(fileDuration * 1000. * 1000.));

        // lets clean up
    //XThrowIfError (AUGraphStop (theGraph), "AUGraphStop");
    //XThrowIfError (AUGraphUninitialize (theGraph), "AUGraphUninitialize");
    //XThrowIfError (AudioFileClose (audioFile), "AudioFileClose");
    //XThrowIfError (AUGraphClose (theGraph), "AUGraphClose");
    
    return 0;
}    


