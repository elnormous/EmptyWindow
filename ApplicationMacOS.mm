//
//  EmptyWindow
//

#include <iostream>
#include <stdexcept>
#include "ApplicationMacOS.hpp"

@interface AppDelegate: NSObject<NSApplicationDelegate>
{
    emptywindow::Application* application;
}
@end

@implementation AppDelegate

-(id)initWithApplication:(emptywindow::Application*)initApplication
{
    if (self = [super init])
        application = initApplication;

    return self;
}

-(void)applicationWillFinishLaunching:(__unused NSNotification*)notification
{
}

-(void)applicationDidFinishLaunching:(__unused NSNotification*)notification
{
}

-(void)applicationWillTerminate:(__unused NSNotification*)notification
{
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(__unused NSApplication*)sender
{
    return YES;
}

-(void)applicationDidBecomeActive:(__unused NSNotification*)notification
{
}

-(void)applicationDidResignActive:(__unused NSNotification*)notification
{
}

@end

@interface WindowDelegate: NSObject<NSWindowDelegate>
{
    emptywindow::ApplicationMacOS* application;
}

@end

@implementation WindowDelegate

-(id)initWithApplication:(emptywindow::ApplicationMacOS*)initApplication
{
    if (self = [super init])
    {
        application = initApplication;
    }

    return self;
}

-(void)windowDidResize:(__unused NSNotification*)notification
{
}

@end

namespace emptywindow
{
    ApplicationMacOS::ApplicationMacOS()
    {
        pool = [[NSAutoreleasePool alloc] init];

        appDelegate = [[AppDelegate alloc] initWithApplication:this];

        NSApplication* sharedApplication = [NSApplication sharedApplication];
        [sharedApplication activateIgnoringOtherApps:YES];
        [sharedApplication setDelegate:appDelegate];

        NSMenu* mainMenu = [[[NSMenu alloc] initWithTitle:@"Main Menu"] autorelease];

        // Apple menu
        NSMenuItem* mainMenuItem = [mainMenu addItemWithTitle:@"Apple"
                                                       action:nil
                                                keyEquivalent:@""];

        NSMenu* applicationMenu = [[[NSMenu alloc] init] autorelease];
        mainMenuItem.submenu = applicationMenu;

        NSString* bundleName = NSBundle.mainBundle.infoDictionary[@"CFBundleDisplayName"];
        if (!bundleName)
            bundleName = NSBundle.mainBundle.infoDictionary[@"CFBundleName"];

        [applicationMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"About", nil), bundleName]
                                   action:@selector(orderFrontStandardAboutPanel:)
                            keyEquivalent:@""];

        [applicationMenu addItem:[NSMenuItem separatorItem]];

        NSMenuItem* servicesItem = [applicationMenu addItemWithTitle:NSLocalizedString(@"Services", nil)
                                                              action:nil
                                                       keyEquivalent:@""];

        NSMenu* servicesMenu = [[[NSMenu alloc] init] autorelease];
        servicesItem.submenu = servicesMenu;
        sharedApplication.servicesMenu = servicesMenu;

        [applicationMenu addItem:[NSMenuItem separatorItem]];

        [applicationMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"Hide", nil), bundleName]
                                   action:@selector(hide:)
                            keyEquivalent:@"h"];

        NSMenuItem* hideOthersItem = [applicationMenu addItemWithTitle:NSLocalizedString(@"Hide Others", nil)
                                                                action:@selector(hideOtherApplications:)
                                                         keyEquivalent:@"h"];
        hideOthersItem.keyEquivalentModifierMask = NSEventModifierFlagOption | NSEventModifierFlagCommand;

        [applicationMenu addItemWithTitle:NSLocalizedString(@"Show All", nil)
                                   action:@selector(unhideAllApplications:)
                            keyEquivalent:@""];

        [applicationMenu addItem:[NSMenuItem separatorItem]];

        [applicationMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"Quit", nil), bundleName]
                                   action:@selector(terminate:)
                            keyEquivalent:@"q"];

        // View menu
        NSMenuItem* viewItem = [mainMenu addItemWithTitle:NSLocalizedString(@"View", nil)
                                                   action:nil
                                            keyEquivalent:@""];

        NSMenu* viewMenu = [[[NSMenu alloc] initWithTitle:NSLocalizedString(@"View", nil)] autorelease];
        viewItem.submenu = viewMenu;

        // Window menu
        NSMenuItem* windowsItem = [mainMenu addItemWithTitle:NSLocalizedString(@"Window", nil)
                                                      action:nil
                                               keyEquivalent:@""];

        NSMenu* windowsMenu = [[[NSMenu alloc] initWithTitle:NSLocalizedString(@"Window", nil)] autorelease];

        [windowsMenu addItemWithTitle:NSLocalizedString(@"Minimize", nil)
                               action:@selector(performMiniaturize:)
                        keyEquivalent:@"m"];

        [windowsMenu addItemWithTitle:NSLocalizedString(@"Zoom", nil)
                               action:@selector(performZoom:)
                        keyEquivalent:@""];

        windowsItem.submenu = windowsMenu;
        sharedApplication.windowsMenu = windowsMenu;

        // Help menu
        NSMenuItem* helpItem = [mainMenu addItemWithTitle:NSLocalizedString(@"Window", nil)
                                                   action:nil
                                            keyEquivalent:@""];

        NSMenu* helpMenu = [[[NSMenu alloc] initWithTitle:NSLocalizedString(@"Help", nil)] autorelease];
        helpItem.submenu = helpMenu;

        [helpMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", bundleName, NSLocalizedString(@"Help", nil)]
                            action:@selector(showHelp:)
                     keyEquivalent:@"?"];

        sharedApplication.helpMenu = helpMenu;

        sharedApplication.mainMenu = mainMenu;

        // create window
        screen = [NSScreen mainScreen];

        CGSize windowSize;
        windowSize.width = round(screen.frame.size.width * 0.6);
        windowSize.height = round(screen.frame.size.height * 0.6);

        const NSRect frame = NSMakeRect(round(screen.frame.size.width / 2.0F - windowSize.width / 2.0F),
                                        round(screen.frame.size.height / 2.0F - windowSize.height / 2.0F),
                                        windowSize.width, windowSize.height);

        const NSWindowStyleMask windowStyleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;

        window  = [[NSWindow alloc] initWithContentRect:frame
                                              styleMask:windowStyleMask
                                                backing:NSBackingStoreBuffered
                                                  defer:NO
                                                 screen:screen];
        [window setReleasedWhenClosed:NO];

        window.acceptsMouseMovedEvents = YES;
        windowDelegate = [[WindowDelegate alloc] initWithApplication:this];
        window.delegate = windowDelegate;

        [window setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
        [window setTitle:@"EmptyWindow"];

        const NSRect windowFrame = [NSWindow contentRectForFrameRect:[window frame]
                                                           styleMask:[window styleMask]];

        content = [[NSView alloc] initWithFrame:windowFrame];

        window.contentView = content;
        [window makeKeyAndOrderFront:nil];
    }

    ApplicationMacOS::~ApplicationMacOS()
    {
        [content release];
        window.delegate = nil;
        [windowDelegate release];
        [window release];
        [appDelegate release];
        [pool release];
    }

    void ApplicationMacOS::run()
    {
        NSApplication* sharedApplication = [NSApplication sharedApplication];
        [sharedApplication run];
    }
}

int main()
{
    try
    {
        emptywindow::ApplicationMacOS application;
        application.run();

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
