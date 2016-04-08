#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PluginIAP/PluginIAP.h"

class HelloWorld : public cocos2d::Layer, public sdkbox::IAPListener
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onShowAds(cocos2d::Ref* sender);
    void onRequestIAP(cocos2d::Ref* sender);
    void onRestoreIAP(cocos2d::Ref* sender);
    void onIAP(cocos2d::Ref* sender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:

    void updateIAP(const std::vector<sdkbox::Product>& products);

    virtual void onInitialized(bool ok) override;

    virtual void onSuccess(sdkbox::Product const& p) override;

    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;

    virtual void onCanceled(sdkbox::Product const& p) override;

    virtual void onRestored(sdkbox::Product const& p) override;

    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;

    virtual void onProductRequestFailure(const std::string &msg) override;

    void onRestoreComplete(bool ok, const std::string &msg);

    void createTestMenu();

    cocos2d::CCMenu* _iapMenu;
    std::vector<sdkbox::Product> _products;
    cocos2d::Label* _txtCoin;
    int _coinCount;
};

#endif // __HELLOWORLD_SCENE_H__
