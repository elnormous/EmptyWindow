//
//  EmptyWindow
//

#include <iostream>
#include <stdexcept>
#include "ApplicationTVOS.hpp"

emptywindow::ApplicationTVOS* sharedApplication;

@interface AppDelegate: UIResponder<UIApplicationDelegate>

@end

@implementation AppDelegate

-(BOOL)application:(__unused UIApplication*)application willFinishLaunchingWithOptions:(__unused NSDictionary*)launchOptions
{
    sharedApplication->createWindow();

    return YES;
}

-(BOOL)application:(__unused UIApplication*)application didFinishLaunchingWithOptions:(__unused NSDictionary*)launchOptions
{
    return YES;
}

-(void)applicationDidBecomeActive:(__unused UIApplication*)application
{
}

-(void)applicationWillResignActive:(__unused UIApplication*)application
{
}

-(void)applicationDidEnterBackground:(__unused UIApplication*)application
{
}

-(void)applicationWillEnterForeground:(__unused UIApplication*)application
{
}

-(void)applicationWillTerminate:(__unused UIApplication*)application
{
}

-(void)applicationDidReceiveMemoryWarning:(__unused UIApplication*)application
{
}

@end

@interface ViewController: UIViewController
{
    emptywindow::ApplicationTVOS* application;
}

@end

@implementation ViewController

-(id)initWithApplication:(emptywindow::ApplicationTVOS*)initApplication
{
    if (self = [super init])
        application = initApplication;

    return self;
}

-(void)textFieldDidChange:(__unused id)sender
{
}

-(void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    [super viewWillTransitionToSize:size withTransitionCoordinator:coordinator];
}

-(void)deviceOrientationDidChange:(NSNotification*)note
{
}

@end

namespace emptywindow
{
    ApplicationTVOS::ApplicationTVOS()
    {
        sharedApplication = this;
        pool = [[NSAutoreleasePool alloc] init];
    }

    ApplicationTVOS::~ApplicationTVOS()
    {
        if (content) [content release];
        if (window)
        {
            window.rootViewController = nil;
            [window release];
        }
        if (pool) [pool release];
    }

    void ApplicationTVOS::createWindow()
    {
        screen = [UIScreen mainScreen];

        window = [[UIWindow alloc] initWithFrame:[screen bounds]];

        viewController = [[[ViewController alloc] initWithApplication:this] autorelease];
        window.rootViewController = viewController;

        CGRect windowFrame = [window bounds];

        content = [[UIView alloc] initWithFrame:windowFrame];
        content.contentScaleFactor = screen.scale;
        viewController.view = content;

        [window makeKeyAndVisible];
    }

    void ApplicationTVOS::run(int argc, char* argv[])
    {
        UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}

int main(int argc, char* argv[])
{
    try
    {
        emptywindow::ApplicationTVOS application;
        application.run(argc, argv);

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (...)
    {
        return EXIT_FAILURE;
    }
}
