#include "HelloWorldScene.h"
#if COCOS2D_VERSION >= 0x00030200
#include "ui/CocosGUI.h"
#endif

#define SCREENLOG_IMPLEMENTATION
#include "ScreenLog.h"

USING_NS_CC;
using namespace sdkbox;

#define kLevelLeaderBoardId "1434"
#define kSoldierAchievementId "3622"

#undef CCLOG
#define CCLOG INFO

template <typename T> std::string tostr(const T& t) { std::ostringstream os; os<<t; return os.str(); }

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    ScreenLog::getInstance()->setLevelMask( LL_DEBUG | LL_INFO | LL_WARNING | LL_ERROR | LL_FATAL );
    ScreenLog::getInstance()->setTimeoutSeconds( 0xFFFF );
    ScreenLog::getInstance()->attachToScene( scene );

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    CCLOG("Sample Startup");

    // add logo
    auto winsize = Director::getInstance()->getWinSize();
    auto logo = Sprite::create("Logo.png");
    auto logoSize = logo->getContentSize();
    logo->setPosition(Vec2(logoSize.width / 2,
                           winsize.height - logoSize.height / 2));
    addChild(logo);

    // add quit button
    auto label = Label::createWithSystemFont("QUIT", "sans", 32);
    auto quit = MenuItemLabel::create(label, [](Ref*){
        exit(0);
    });
    auto labelSize = label->getContentSize();
    quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
                           -winsize.height / 2 + labelSize.height / 2 + 16));
    addChild(Menu::create(quit, NULL));

    createTestMenu();

    return true;
}

void HelloWorld::createTestMenu()
{
    auto winsize = Director::getInstance()->getWinSize();

    IAP::setDebug(true);
    IAP::setListener(this);
    IAP::init();

    MenuItemFont::setFontSize(48);

    _coinCount = 0;

    _txtCoin = Label::create("0", "sans", 32);
    _txtCoin->setAnchorPoint(Vec2(0, 0));
    _txtCoin->setPosition(Vec2(winsize.width/2, _txtCoin->getContentSize().height));
    addChild(_txtCoin);

    auto item = MenuItemFont::create("Load", this, menu_selector(HelloWorld::onRequestIAP));
    CCMenuItemFont *item2 = CCMenuItemFont::create("Restore", this, menu_selector(HelloWorld::onRestoreIAP));

    CCMenu *menu = CCMenu::create(item, item2, NULL);
    menu->alignItemsHorizontallyWithPadding(20);
    menu->setPosition(winsize.width/2, winsize.height-50);
    addChild(menu);

    _iapMenu = CCMenu::create();
    _iapMenu->setPosition(winsize.width/2, winsize.height/2);
    addChild(_iapMenu);

    Product test;
    test.name = "remove_ads";

    _products.push_back(test);
    updateIAP(_products);
}

void HelloWorld::onShowAds(cocos2d::Ref *sender)
{
    CCLOG("Show Ads");
}

void HelloWorld::onRequestIAP(cocos2d::Ref* sender)
{
    IAP::refresh();
}

void HelloWorld::onRestoreIAP(cocos2d::Ref* sender)
{
    IAP::restore();
}

void HelloWorld::onIAP(cocos2d::Ref *sender)
{
    auto btn = static_cast<Node*>(sender);
    Product* p = (Product*)btn->getUserData();

    CCLOG("Start IAP %s", p->name.c_str());
    IAP::purchase(p->name);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onInitialized(bool ok)
{
    CCLOG("%s : %d", __func__, ok);
}

void HelloWorld::onSuccess(const Product &p)
{
    if (p.name == "coin_package") {
        _coinCount += 1000;
        _txtCoin->setString(tostr(_coinCount));
    }
    else if (p.name == "coin_package2") {
        _coinCount += 5000;
        _txtCoin->setString(tostr(_coinCount));
    }
    else if (p.name == "remove_ads") {
        CCLOG("Remove Ads");
    }

    CCLOG("Purchase Success: %s", p.id.c_str());
    INFO("receiptCipheredPayload=%s", p.receiptCipheredPayload.c_str());
    INFO("receipt=%s", p.receipt.c_str());
    INFO("transactionID=%s", p.transactionID.c_str());
}

void HelloWorld::onFailure(const Product &p, const std::string &msg)
{
    CCLOG("Purchase Failed: %s", msg.c_str());

}

void HelloWorld::onCanceled(const Product &p)
{
    CCLOG("Purchase Canceled: %s", p.id.c_str());
}

void HelloWorld::onRestored(const Product& p)
{
    CCLOG("Purchase Restored: %s", p.name.c_str());
}

void HelloWorld::updateIAP(const std::vector<sdkbox::Product>& products)
{
    //
    _iapMenu->removeAllChildren();
    _products = products;

    int posX = 0;
    int posY = 0;

    for (int i=0; i < _products.size(); i++)
    {
        CCLOG("IAP: ========= IAP Item =========");
        CCLOG("IAP: Name: %s", _products[i].name.c_str());
        CCLOG("IAP: ID: %s", _products[i].id.c_str());
        CCLOG("IAP: Title: %s", _products[i].title.c_str());
        CCLOG("IAP: Desc: %s", _products[i].description.c_str());
        CCLOG("IAP: Price: %s", _products[i].price.c_str());
        CCLOG("IAP: Price Currency: %s", _products[i].currencyCode.c_str());
        CCLOG("IAP: Price Value: %f", _products[i].priceValue);

        auto btn = CCMenuItemFont::create(_products[i].name.c_str(), CC_CALLBACK_1(HelloWorld::onIAP, this) );
        btn->setColor(Color3B::WHITE);
        btn->setUserData(&_products[i]);
        btn->setPosition(CCPoint(posX, posY));
        _iapMenu->addChild(btn);
        posY += 50;
    }

    _iapMenu->alignItemsVerticallyWithPadding(20);
}

void HelloWorld::onProductRequestSuccess(const std::vector<Product> &products)
{
    updateIAP(products);
}

void HelloWorld::onProductRequestFailure(const std::string &msg)
{
    CCLOG("Fail to load products");
}

void HelloWorld::onRestoreComplete(bool ok, const std::string &msg)
{
    CCLOG("%s:%d:%s", __func__, ok, msg.data());
}

#if (COCOS2D_VERSION == 0x00030000) // maybe more cocos2d version if you find
// extern "C" {
//     size_t fwrite$UNIX2003( const void *a, size_t b, size_t c, FILE *d )
//     {
//         return fwrite(a, b, c, d);
//     }
//     char* strerror$UNIX2003( int errnum )
//     {
//         return strerror(errnum);
//     }
// }
#endif // (COCOS2D_VERSION == 0x00030000)
