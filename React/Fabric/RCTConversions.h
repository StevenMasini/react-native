
/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <UIKit/UIKit.h>

#import <react/components/view/AccessibilityPrimitives.h>
#import <react/components/view/primitives.h>
#import <react/graphics/Color.h>
#import <react/graphics/Geometry.h>
#import <react/graphics/Transform.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * `RNWrapManagedObject` and `RNUnwrapManagedObject` are wrapper functions that convert ARC-managed objects into
 * `std::shared_ptr<void>` and vice-versa. It's a very useful mechanism when we need to pass Objective-C objects through
 * pure C++ code, pass blocks into C++ lambdas, and so on.
 *
 * The idea behind this mechanism is quite simple but tricky: When we instantiate a C++ shared pointer for a managed
 * object, we practically call `CFRetain` for it once and then we represent this single retaining operation as a counter
 * inside the shared pointer; when the counter became zero, we call `CFRelease` on the object. In this model, one bump
 * of ARC-managed counter is represented as multiple bumps of C++ counter, so we can have multiple counters for the same
 * object that form some kind of counters tree.
 */
inline std::shared_ptr<void> RNWrapManagedObject(id object)
{
  return std::shared_ptr<void>((__bridge_retained void *)object, CFRelease);
}

inline id RNUnwrapManagedObject(std::shared_ptr<void> const &object)
{
  return (__bridge id)object.get();
}

inline NSString *RCTNSStringFromString(const std::string &string, const NSStringEncoding &encoding = NSUTF8StringEncoding) {
  return [NSString stringWithCString:string.c_str() encoding:encoding];
}

inline NSString *_Nullable RCTNSStringFromStringNilIfEmpty(const std::string &string, const NSStringEncoding &encoding = NSUTF8StringEncoding) {
  return string.empty() ? nil : RCTNSStringFromString(string, encoding);
}

inline std::string RCTStringFromNSString(NSString *string, const NSStringEncoding &encoding = NSUTF8StringEncoding) {
  return [string cStringUsingEncoding:encoding];
}

inline UIColor *_Nullable RCTUIColorFromSharedColor(const facebook::react::SharedColor &sharedColor) {
  return sharedColor ? [UIColor colorWithCGColor:sharedColor.get()] : nil;
}


inline CF_RETURNS_NOT_RETAINED CGColorRef RCTCGColorRefUnretainedFromSharedColor(const facebook::react::SharedColor &sharedColor) {
  return sharedColor ? sharedColor.get() : nil;
}


inline CF_RETURNS_RETAINED CGColorRef RCTCGColorRefFromSharedColor(const facebook::react::SharedColor &sharedColor) {
  return sharedColor ? CGColorCreateCopy(sharedColor.get()) : nil;
}

inline CGPoint RCTCGPointFromPoint(const facebook::react::Point &point) {
  return {point.x, point.y};
}

inline CGSize RCTCGSizeFromSize(const facebook::react::Size &size) {
  return {size.width, size.height};
}

inline CGRect RCTCGRectFromRect(const facebook::react::Rect &rect) {
  return {RCTCGPointFromPoint(rect.origin), RCTCGSizeFromSize(rect.size)};
}

inline UIEdgeInsets RCTUIEdgeInsetsFromEdgeInsets(const facebook::react::EdgeInsets &edgeInsets) {
  return {edgeInsets.top, edgeInsets.left, edgeInsets.bottom, edgeInsets.right};
}

inline UIAccessibilityTraits RCTUIAccessibilityTraitsFromAccessibilityTraits(facebook::react::AccessibilityTraits accessibilityTraits) {
  using AccessibilityTraits = facebook::react::AccessibilityTraits;
  UIAccessibilityTraits result = UIAccessibilityTraitNone;
  if ((accessibilityTraits & AccessibilityTraits::Button) != AccessibilityTraits::None) { result |= UIAccessibilityTraitButton; }
  if ((accessibilityTraits & AccessibilityTraits::Link) != AccessibilityTraits::None) { result |= UIAccessibilityTraitLink; }
  if ((accessibilityTraits & AccessibilityTraits::Image) != AccessibilityTraits::None) { result |= UIAccessibilityTraitImage; }
  if ((accessibilityTraits & AccessibilityTraits::Selected) != AccessibilityTraits::None) { result |= UIAccessibilityTraitSelected; }
  if ((accessibilityTraits & AccessibilityTraits::PlaysSound) != AccessibilityTraits::None) { result |= UIAccessibilityTraitPlaysSound; }
  if ((accessibilityTraits & AccessibilityTraits::KeyboardKey) != AccessibilityTraits::None) { result |= UIAccessibilityTraitKeyboardKey; }
  if ((accessibilityTraits & AccessibilityTraits::StaticText) != AccessibilityTraits::None) { result |= UIAccessibilityTraitStaticText; }
  if ((accessibilityTraits & AccessibilityTraits::SummaryElement) != AccessibilityTraits::None) { result |= UIAccessibilityTraitSummaryElement; }
  if ((accessibilityTraits & AccessibilityTraits::NotEnabled) != AccessibilityTraits::None) { result |= UIAccessibilityTraitNotEnabled; }
  if ((accessibilityTraits & AccessibilityTraits::UpdatesFrequently) != AccessibilityTraits::None) { result |= UIAccessibilityTraitUpdatesFrequently; }
  if ((accessibilityTraits & AccessibilityTraits::SearchField) != AccessibilityTraits::None) { result |= UIAccessibilityTraitSearchField; }
  if ((accessibilityTraits & AccessibilityTraits::StartsMediaSession) != AccessibilityTraits::None) { result |= UIAccessibilityTraitStartsMediaSession; }
  if ((accessibilityTraits & AccessibilityTraits::Adjustable) != AccessibilityTraits::None) { result |= UIAccessibilityTraitAdjustable; }
  if ((accessibilityTraits & AccessibilityTraits::AllowsDirectInteraction) != AccessibilityTraits::None) { result |= UIAccessibilityTraitAllowsDirectInteraction; }
  if ((accessibilityTraits & AccessibilityTraits::CausesPageTurn) != AccessibilityTraits::None) { result |= UIAccessibilityTraitCausesPageTurn; }
  if ((accessibilityTraits & AccessibilityTraits::Header) != AccessibilityTraits::None) { result |= UIAccessibilityTraitHeader; }
  return result;
};

inline CATransform3D RCTCATransform3DFromTransformMatrix(const facebook::react::Transform &transformMatrix) {
  return {
    (CGFloat)transformMatrix.matrix[0],
    (CGFloat)transformMatrix.matrix[1],
    (CGFloat)transformMatrix.matrix[2],
    (CGFloat)transformMatrix.matrix[3],
    (CGFloat)transformMatrix.matrix[4],
    (CGFloat)transformMatrix.matrix[5],
    (CGFloat)transformMatrix.matrix[6],
    (CGFloat)transformMatrix.matrix[7],
    (CGFloat)transformMatrix.matrix[8],
    (CGFloat)transformMatrix.matrix[9],
    (CGFloat)transformMatrix.matrix[10],
    (CGFloat)transformMatrix.matrix[11],
    (CGFloat)transformMatrix.matrix[12],
    (CGFloat)transformMatrix.matrix[13],
    (CGFloat)transformMatrix.matrix[14],
    (CGFloat)transformMatrix.matrix[15]
  };
}

inline facebook::react::Point RCTPointFromCGPoint(const CGPoint &point) {
  return {point.x, point.y};
}

inline facebook::react::Size RCTSizeFromCGSize(const CGSize &size) {
  return {size.width, size.height};
}

inline facebook::react::Rect RCTRectFromCGRect(const CGRect &rect) {
  return {RCTPointFromCGPoint(rect.origin), RCTSizeFromCGSize(rect.size)};
}

inline facebook::react::EdgeInsets RCTEdgeInsetsFromUIEdgeInsets(const UIEdgeInsets &edgeInsets) {
  return {edgeInsets.top, edgeInsets.left, edgeInsets.bottom, edgeInsets.right};
}

NS_ASSUME_NONNULL_END
