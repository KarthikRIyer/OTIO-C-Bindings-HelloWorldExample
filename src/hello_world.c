#include <copentime/rationalTime.h>
#include <copentimelineio/externalReference.h>
#include <copentimelineio/clip.h>
#include <copentimelineio/transition.h>
#include <copentimelineio/track.h>
#include <copentimelineio/stack.h>
#include <copentimelineio/timeline.h>
#include <stddef.h>


/**
 * This example demonstrates the use of OpenTimelineIO to create a
 * simple timeline with two clips and a crossfade transition between them.
 *
 * To keep the example simple, we assume that we already know the frame rate and duration
 * of the clips we're using. In an actual application you might need to query for these using
 * a framework like ffmpeg.
 *
 * We will have two clips, each of 5 seconds length.
 * The first clip will be cut to a length of 1.25 seconds.
 * The second clip will be cut from 0.25 seconds to 2.00 seconds.
 * We'll add a crossfade transition of half a second between these clips.
 */
int main() {

    double frameRate = 24;

    // Create first clip (Hello World Clip)
    RationalTime startTime = RationalTime_create(0, frameRate);
    RationalTime duration = RationalTime_from_seconds(5);
    duration = RationalTime_rescaled_to(duration, 24);
    OptionalTimeRange availableRange = OptionalTimeRange_create(
            TimeRange_create_with_start_time_and_duration(startTime, duration));
    // Available range is the timeRange of the complete media available.
    // External Reference points to a local file or a media URL.
    ExternalReference *helloWorldMediaReference =
            ExternalReference_create("file:///home/karthik/hello_world_example/media/hello_world.mp4",
                                     availableRange,
                                     NULL);
    // Cut hello world clip at 1.25 s
    RationalTime cutTime = RationalTime_from_seconds(1.25);
    cutTime = RationalTime_rescaled_to(cutTime, 24);
    OptionalTimeRange sourceRange = OptionalTimeRange_create(TimeRange_create_with_duration(cutTime));
    // Source range is the part of the available range that we want to add to the timeline
    Clip *helloWorldClip = Clip_create("hello_world",
                                       (MediaReference *) helloWorldMediaReference,
                                       sourceRange,
                                       NULL);
    OTIO_RETAIN(helloWorldMediaReference);
    OTIO_RETAIN(helloWorldClip);
    // OTIO's memory management method is a little different from what is generally used in C/C++.
    // The C-bindings wrap it in macros. Every OTIO object created should be retained after creation
    // and released after use using OTIO_RETAIN and OTIO_RELEASE respectively.

    ExternalReference *welcomeMediaReference =
            ExternalReference_create("file:///home/karthik/hello_world_example/media/welcome.mp4",
                                     availableRange,
                                     NULL);
    // Cut welcome clip to 0.25s - 2.00 s
    RationalTime cutStartTime = RationalTime_from_seconds(0.25);
    cutStartTime = RationalTime_rescaled_to(cutStartTime, 24);
    RationalTime cutEndTime = RationalTime_from_seconds(2.0);
    cutEndTime = RationalTime_rescaled_to(cutEndTime, 24);
    RationalTime cutDuration = RationalTime_subtract(cutEndTime, cutStartTime);
    sourceRange = OptionalTimeRange_create(TimeRange_create_with_start_time_and_duration(cutStartTime, cutDuration));
    Clip *welcomeClip = Clip_create("welcome",
                                    (MediaReference *) welcomeMediaReference,
                                    sourceRange,
                                    NULL);
    OTIO_RETAIN(welcomeMediaReference);
    OTIO_RETAIN(welcomeClip);


    OptionalRationalTime transitionInOffset = OptionalRationalTime_create(RationalTime_create(6, 24));
    OptionalRationalTime transitionOutOffset = OptionalRationalTime_create(RationalTime_create(6, 24));
    Transition *crossfade = Transition_create("crossfade", TransitionType_SMPTE_Dissolve, transitionInOffset,
                                              transitionOutOffset, NULL);
    OTIO_RETAIN(crossfade);

    // Here we add our clips and transition to a track. In this example we do not have any audio associated with the clips.
    // So we will have just one Video Track.
    Track *track = Track_create("Track-1", OptionalTimeRange_create_null(), TrackKind_Video, NULL);
    OTIOErrorStatus *errorStatus = OTIOErrorStatus_create();
    OTIO_RETAIN(track);
    Track_append_child(track, (Composable *) helloWorldClip, errorStatus);
    Track_append_child(track, (Composable *) crossfade, errorStatus);
    Track_append_child(track, (Composable *) welcomeClip, errorStatus);

    // We need to add all tracks to a Stack before we can create a timeline.
    Stack *stack = Stack_create("Stack", OptionalTimeRange_create_null(), NULL, NULL, NULL);
    OTIO_RETAIN(stack);
    Stack_append_child(stack, (Composable *) track, errorStatus);

    Timeline *timeline = Timeline_create("Timeline", OptionalRationalTime_create_null(), NULL);
    OTIO_RETAIN(timeline);
    Timeline_set_tracks(timeline, stack);

    // There are two ways we can serialize a timeline to an otio file:
    // In the first method, we create an 'any' object from our timeline. This can then
    // be serialized with the serialize_json_to_file() method. This can come in handy,
    // if whatever we want to serialize is not an OTIOSerializableObject. For example,
    // any opentime object (RationalTime, TimeRange, TimeTransform) or just some metadata.
    //    Any *timeline_any =
    //            create_safely_typed_any_serializable_object((OTIOSerializableObject *) timeline);
    //    serialize_json_to_file(clip_any, fileName, errorStatus, 4);
    // In the second method we can directly serialize an OTIOSerializableObject, as shown below.
    SerializableObject_to_json_file((OTIOSerializableObject *) timeline,
                                    "hello_world_example.otio",
                                    errorStatus,
                                    4);

    OTIO_RELEASE(timeline);
    OTIO_RELEASE(stack);
    OTIO_RELEASE(track);
    OTIO_RELEASE(crossfade);
    OTIO_RELEASE(welcomeClip);
    OTIO_RELEASE(welcomeMediaReference);
    OTIO_RELEASE(helloWorldClip);
    OTIO_RELEASE(helloWorldMediaReference);

    return 0;
}