#ifndef __OPENEXR_INCLUDES__H_
#define __OPENEXR_INCLUDES__H_

#include <assert.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <glew/GL/glew.h>

#include <EnvmapImage.h>
#include <Iex.h>
#include <IexBaseExc.h>
#include <IexErrnoExc.h>
#include <IexMacros.h>
#include <IexMathExc.h>
#include <IexThrowErrnoExc.h>
#include <IlmBaseConfig.h>
#include <IlmThread.h>
#include <IlmThreadMutex.h>
#include <IlmThreadPool.h>
#include <IlmThreadSemaphore.h>
#include <Image.h>
#include <ImathBox.h>
#include <ImathBoxAlgo.h>
#include <ImathColor.h>
#include <ImathColorAlgo.h>
#include <ImathEuler.h>
#include <ImathExc.h>
#include <ImathFrame.h>
#include <ImathFrustum.h>
#include <ImathFun.h>
#include <ImathGL.h>
#include <ImathGLU.h>
#include <ImathHalfLimits.h>
#include <ImathInt64.h>
#include <ImathInterval.h>
#include <ImathLimits.h>
#include <ImathLine.h>
#include <ImathLineAlgo.h>
#include <ImathMath.h>
#include <ImathMatrix.h>
#include <ImathMatrixAlgo.h>
#include <ImathPlane.h>
#include <ImathPlatform.h>
#include <ImathQuat.h>
#include <ImathRandom.h>
#include <ImathRoots.h>
#include <ImathShear.h>
#include <ImathSphere.h>
#include <ImathVec.h>
#include <ImathVecAlgo.h>
#include <ImfAcesFile.h>
#include <ImfArray.h>
#include <ImfAttribute.h>
#include <ImfAutoArray.h>
#include <ImfB44Compressor.h>
#include <ImfBoxAttribute.h>
#include <ImfCRgbaFile.h>
#include <ImfChannelList.h>
#include <ImfChannelListAttribute.h>
#include <ImfCheckedArithmetic.h>
#include <ImfChromaticities.h>
#include <ImfChromaticitiesAttribute.h>
#include <ImfCompression.h>
#include <ImfCompressionAttribute.h>
#include <ImfCompressor.h>
#include <ImfConvert.h>
#include <ImfDoubleAttribute.h>
#include <ImfEnvmap.h>
#include <ImfEnvmapAttribute.h>
#include <ImfFloatAttribute.h>
#include <ImfFrameBuffer.h>
#include <ImfFramesPerSecond.h>
#include <ImfHeader.h>
#include <ImfHuf.h>
#include <ImfIO.h>
#include <ImfInputFile.h>
#include <ImfInt64.h>
#include <ImfIntAttribute.h>
#include <ImfKeyCode.h>
#include <ImfKeyCodeAttribute.h>
#include <ImfLineOrder.h>
#include <ImfLineOrderAttribute.h>
#include <ImfLut.h>
#include <ImfMatrixAttribute.h>
#include <ImfMisc.h>
#include <ImfMultiView.h>
#include <ImfName.h>
#include <ImfOpaqueAttribute.h>
#include <ImfOutputFile.h>
#include <ImfPixelType.h>
#include <ImfPizCompressor.h>
#include <ImfPreviewImage.h>
#include <ImfPreviewImageAttribute.h>
#include <ImfPxr24Compressor.h>
#include <ImfRational.h>
#include <ImfRationalAttribute.h>
#include <ImfRgba.h>
#include <ImfRgbaFile.h>
#include <ImfRgbaYca.h>
#include <ImfRleCompressor.h>
#include <ImfScanLineInputFile.h>
#include <ImfStandardAttributes.h>
#include <ImfStdIO.h>
#include <ImfStringAttribute.h>
#include <ImfStringVectorAttribute.h>
#include <ImfTestFile.h>
#include <ImfThreading.h>
#include <ImfTileDescription.h>
#include <ImfTileDescriptionAttribute.h>
#include <ImfTileOffsets.h>
#include <ImfTiledInputFile.h>
#include <ImfTiledMisc.h>
#include <ImfTiledOutputFile.h>
#include <ImfTiledRgbaFile.h>
#include <ImfTimeCode.h>
#include <ImfTimeCodeAttribute.h>
#include <ImfVecAttribute.h>
#include <ImfVersion.h>
#include <ImfWav.h>
#include <ImfXdr.h>
#include <ImfZipCompressor.h>
#include <OpenEXRConfig.h>
#include <OptionParser.h>
#include <b44ExpLogTable.h>
#include <blurImage.h>
#include <compareB44.h>
#include <compareFloat.h>
#include <drawImage.h>
//#include <eLut.h>
#include <fuzzFile.h>
#include <generalInterfaceExamples.h>
#include <generalInterfaceTiledExamples.h>
#include <half.h>
#include <halfFunction.h>
#include <halfLimits.h>
#include <lowLevelIoExamples.h>
#include <makeCubeMap.h>
#include <makeLatLongMap.h>
#include <makeMultiView.h>
#include <makePreview.h>
#include <makeTiled.h>
#include <previewImageExamples.h>
#include <readInputImage.h>
#include <resizeImage.h>
#include <rgbaInterfaceExamples.h>
#include <rgbaInterfaceTiledExamples.h>
/*#include <testArithmetic.h>
#include <testAttributes.h>
#include <testBaseExc.h>
#include <testBitPatterns.h>
#include <testBox.h>
#include <testBoxAlgo.h>
#include <testChannels.h>
#include <testClassification.h>
#include <testColor.h>
#include <testCompression.h>
#include <testConversion.h>
#include <testCopyPixels.h>
#include <testCustomAttributes.h>
#include <testError.h>
#include <testExistingStreams.h>
#include <testExtractEuler.h>
#include <testExtractSHRT.h>
#include <testFrustum.h>
#include <testFun.h>
#include <testFunction.h>
#include <testFuzzScanLines.h>
#include <testFuzzTiles.h>
#include <testHuf.h>
#include <testInvert.h>
#include <testIsComplete.h>
#include <testLimits.h>
#include <testLineAlgo.h>
#include <testLineOrder.h>
#include <testLut.h>
#include <testMagic.h>
#include <testMatrix.h>
#include <testMultiView.h>
#include <testNativeFormat.h>
#include <testPreviewImage.h>
#include <testQuat.h>
#include <testQuatSetRotation.h>
#include <testQuatSlerp.h>
#include <testRandom.h>
#include <testRgba.h>
#include <testRgbaThreading.h>
#include <testRoots.h>
#include <testSampleImages.h>
#include <testScanLineApi.h>
#include <testSharedFrameBuffer.h>
#include <testShear.h>
#include <testSize.h>
#include <testStandardAttributes.h>
#include <testTiledCompression.h>
#include <testTiledCopyPixels.h>
#include <testTiledLineOrder.h>
#include <testTiledRgba.h>
#include <testTiledYa.h>
#include <testVec.h>
#include <testWav.h>
#include <testXdr.h>
#include <testYca.h>*/
#include <tmpDir.h>
//#include <toFloat.h>

#include "TypeBuffer.h"
#include "LightExtractor.h"
#include "Reader.h"
#include "Texture.h"

#endif