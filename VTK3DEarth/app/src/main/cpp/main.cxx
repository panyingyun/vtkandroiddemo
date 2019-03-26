/*
 * Author: panyingyun(at)gmail.com
 *
 * Description: Demo（Earth） for Study VTK
 *
 */
#include <jni.h>
#include <errno.h>
#include <sstream>

#include <vtkActor.h>
#include <vtkCellData.h>
#include <vtkColorTransferFunction.h>
#include <vtkDataArray.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkJPEGReader.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTexture.h>
#include <vtkCamera.h>
#include <vtkDebugLeaks.h>
#include <vtkGlyph3D.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkAndroidRenderWindowInteractor.h>
#include <vtkCommand.h>

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "NativeVTK", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "NativeVTK", __VA_ARGS__))

extern "C"
{
  JNIEXPORT jlong JNICALL Java_com_kitware_JavaVTK_JavaVTKLib_init(JNIEnv *env, jobject obj, jint width, jint height);
  JNIEXPORT void JNICALL Java_com_kitware_JavaVTK_JavaVTKLib_render(JNIEnv *env, jobject obj, jlong renWinP);
  JNIEXPORT void JNICALL Java_com_kitware_JavaVTK_JavaVTKLib_onKeyEvent(JNIEnv *env, jobject obj, jlong udp,
                                                                        jboolean down, jint keyCode, jint metaState, jint repeatCount);
  JNIEXPORT void JNICALL Java_com_kitware_JavaVTK_JavaVTKLib_onMotionEvent(JNIEnv *env, jobject obj, jlong udp,
                                                                           jint action,
                                                                           jint eventPointer,
                                                                           jint numPtrs,
                                                                           jfloatArray xPos, jfloatArray yPos,
                                                                           jintArray ids, jint metaState);
};

struct userData
{
  vtkRenderWindow *RenderWindow;
  vtkRenderer *Renderer;
  vtkAndroidRenderWindowInteractor *Interactor;
};

// Example of updating text as we go
class vtkExampleCallback : public vtkCommand
{
public:
  static vtkExampleCallback *New()
  {
    return new vtkExampleCallback;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void *)
  {
    // Update cardinality of selection
    double *pos = this->Camera->GetPosition();
    std::ostringstream txt;
    txt << "Camera positioned at: "
        << std::fixed
        << std::setprecision(2)
        << std::setw(6)
        << pos[0] << ", "
        << std::setw(6)
        << pos[1] << ", "
        << std::setw(6)
        << pos[2];
    this->Text->SetInput(txt.str().c_str());
  }

  vtkExampleCallback()
  {
    this->Camera = 0;
    this->Text = 0;
  }

  vtkCamera *Camera;
  vtkTextActor *Text;
};

/*
 * Here is where you would setup your pipeline and other normal VTK logic
 */
JNIEXPORT jlong JNICALL Java_com_kitware_JavaVTK_JavaVTKLib_init(JNIEnv *env, jobject obj, jint width, jint height)
{
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  char jniS[4] = {'j', 'n', 'i', 0};
  renWin->SetWindowInfo(jniS); // tell the system that jni owns the window not us
  renWin->SetSize(width, height);
  vtkNew<vtkRenderer> renderer;
  renWin->AddRenderer(renderer.Get());

  vtkNew<vtkAndroidRenderWindowInteractor> iren;
  iren->SetRenderWindow(renWin);

  // Create SphereSource
  vtkNew<vtkSphereSource> source;
  source->SetRadius(0.5);
  source->SetPhiResolution(80);
  source->SetThetaResolution(80);

  // Create TextureMapToSphere
  //vtkNew<vtkTextureMapToSphere> texturemap;
  //texturemap->SetInputConnection(source->GetOutputPort());

  // Create Texture
  //vtkNew<vtkJPEGReader> jPEGReader;
  //jPEGReader->SetFileName("/mnt/sdcard/earth.jpg");
  //vtkNew<vtkTexture> texture;
  //texture->SetInputConnection(jPEGReader->GetOutputPort());

  // Create Data Set Mapper
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(source->GetOutputPort());

  // Create Actor
  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);
  //actor->SetTexture(texture);

  renderer->AddActor(actor.Get());
  renderer->SetBackground(0.4, 0.5, 0.6);

  vtkNew<vtkTextActor> ta;
  ta->SetInput("Droids Rock");
  ta->GetTextProperty()->SetColor(0.5, 1.0, 0.0);
  ta->SetDisplayPosition(50, 50);
  ta->GetTextProperty()->SetFontSize(32);
  renderer->AddActor(ta.Get());

  vtkNew<vtkExampleCallback> cb;
  cb->Camera = renderer->GetActiveCamera();
  cb->Text = ta.Get();
  iren->AddObserver(vtkCommand::InteractionEvent, cb.Get());

  struct userData *foo = new struct userData();
  foo->RenderWindow = renWin;
  foo->Renderer = renderer.Get();
  foo->Interactor = iren.Get();

  return (jlong)foo;
}

JNIEXPORT void JNICALL Java_com_kitware_JavaVTK_JavaVTKLib_render(JNIEnv *env, jobject obj, jlong udp)
{
  struct userData *foo = (userData *)(udp);
  foo->RenderWindow->SwapBuffersOff(); // android does it
  foo->RenderWindow->Render();
  foo->RenderWindow->SwapBuffersOn(); // reset
}

JNIEXPORT void JNICALL Java_com_kitware_JavaVTK_JavaVTKLib_onKeyEvent(JNIEnv *env, jobject obj, jlong udp,
                                                                      jboolean down, jint keyCode, jint metaState, jint repeatCount)
{
  struct userData *foo = (userData *)(udp);
  foo->Interactor->HandleKeyEvent(down, keyCode, metaState, repeatCount);
}

JNIEXPORT void JNICALL Java_com_kitware_JavaVTK_JavaVTKLib_onMotionEvent(JNIEnv *env, jobject obj, jlong udp,
                                                                         jint action,
                                                                         jint eventPointer,
                                                                         jint numPtrs,
                                                                         jfloatArray xPos, jfloatArray yPos,
                                                                         jintArray ids, jint metaState)
{
  struct userData *foo = (userData *)(udp);

  int xPtr[VTKI_MAX_POINTERS];
  int yPtr[VTKI_MAX_POINTERS];
  int idPtr[VTKI_MAX_POINTERS];

  // only allow VTKI_MAX_POINTERS touches right now
  if (numPtrs > VTKI_MAX_POINTERS)
  {
    numPtrs = VTKI_MAX_POINTERS;
  }

  // fill in the arrays
  jfloat *xJPtr = env->GetFloatArrayElements(xPos, 0);
  jfloat *yJPtr = env->GetFloatArrayElements(yPos, 0);
  jint *idJPtr = env->GetIntArrayElements(ids, 0);
  for (int i = 0; i < numPtrs; ++i)
  {
    xPtr[i] = (int)xJPtr[i];
    yPtr[i] = (int)yJPtr[i];
    idPtr[i] = idJPtr[i];
  }
  env->ReleaseIntArrayElements(ids, idJPtr, 0);
  env->ReleaseFloatArrayElements(xPos, xJPtr, 0);
  env->ReleaseFloatArrayElements(yPos, yJPtr, 0);

  foo->Interactor->HandleMotionEvent(action, eventPointer, numPtrs, xPtr, yPtr, idPtr, metaState);
}
