#include <memory>
#include <iostream>

/* 製作中のカメラモジュール ------------------------------------------- */
class Image {/**/};

/* カメラ撮影用サービス(リソースアクセス制限あり) */
class CameraService {
public:
    /* カメラサービスの取得処理 */
    static std::shared_ptr<CameraService> Open() {

        /*カメラ初期化処理 内容省略*/

        //return std::make_shared<CameraService>();
        // 代わりに関数内クラスを利用する
        struct impl : public CameraService {
          impl() : hoge() {} 
        };
        auto p = std::make_shared<impl>();
        return p;
    }
    /* 撮影画像を受け取るオブジェクトの登録 */
    void SetListener(std::shared_ptr<CameraServiceListener> listener) {
        mListener = listener; 
    }
    /* 撮影開始 */
    void RequestStartRecord() {/**/}
    /* 撮影終了 */
    void RequestStopRecord() {/**/}
    /* カメラリソースの解放処理 */
    ~CameraService() {/**/}

private:
    CameraService(){/**/}
    std::shared_ptr<CameraServiceListener> mListener;
};

class CameraServiceListener {
    /* 画像更新通知 */
    void onUpdate(std::shared_ptr<Image> img) = 0;
};

/* カメラモジュールの利用コード ------------------------------------------- */

class GUIApp : public CameraServiceListener, public std::enable_shared_from_this<GUIApp> {
public:
    virtual ~GUIApp() {/**/}
    void Loop() {/**/}

protected:
    /* アプリケーション開始 */
    void onInit() {
        auto camera = CameraService::Open();
        auto self = shared_from_this();
        camera->SetListener(self);
        mCamera = camera;
    }

    /* 画面描画 */
    void onDraw() { 
        /* draw(mImage.get()) */
    }

    /* 撮影開始ボタン押下 */
    void onTouchStartRecordButton() { 
        mCamera->RequestStartRecord();
    }
    /* 撮影停止ボタン押下 */
    void onTouchStopRecordButton() { 
        mCamera->RequestStopRecord();
    }

    /* 画像更新通知 */
    void onUpdate(Image* img) {
        mImage = img;
        invalidate();
    }

private:
    /* 描画要求 */
    void invalidate() {/**/}

private:
    //std::shared_ptr<CameraService> mCamera; // NG
    std::weak_ptr<CameraService> mCamera; // OK

    //std::shared_ptr<Image> mImage; // NG
    std::weak_ptr<Image> mImage; // OK
};

/* ------------------------------------------- */

int main() {
    std::cout << "start" << std::endl;

    std::shared_ptr<GUIApp> pGUIApp = std::make_shared<GUIApp>();
    pGUIApp.Loop();
    
    std::cout << "end" << std::endl;
}

/* ------------------------------------------- */

