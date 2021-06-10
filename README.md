# OTIO-C-Bindings-HelloWorldExample

This example demonstrates the use of OpenTimelineIO to create a simple timeline with two clips and a crossfade transition between them. Running the example will generate and otio file for this simple timeline.

### How to build and run
```console
git clone --recurse-submodules https://github.com/KarthikRIyer/OTIO-C-Bindings-HelloWorldExample
cd OTIO-C-Bindings-HelloWorldExample
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./src/hello_world
```

#### Generated otio file
```json
{
    "OTIO_SCHEMA": "Timeline.1",
    "metadata": {},
    "name": "Timeline",
    "global_start_time": null,
    "tracks": {
        "OTIO_SCHEMA": "Stack.1",
        "metadata": {},
        "name": "Stack",
        "source_range": null,
        "effects": [],
        "markers": [],
        "children": [
            {
                "OTIO_SCHEMA": "Track.1",
                "metadata": {},
                "name": "Track-1",
                "source_range": null,
                "effects": [],
                "markers": [],
                "children": [
                    {
                        "OTIO_SCHEMA": "Clip.1",
                        "metadata": {},
                        "name": "hello_world",
                        "source_range": {
                            "OTIO_SCHEMA": "TimeRange.1",
                            "duration": {
                                "OTIO_SCHEMA": "RationalTime.1",
                                "rate": 24.0,
                                "value": 30.0
                            },
                            "start_time": {
                                "OTIO_SCHEMA": "RationalTime.1",
                                "rate": 1.0,
                                "value": 0.0
                            }
                        },
                        "effects": [],
                        "markers": [],
                        "media_reference": {
                            "OTIO_SCHEMA": "ExternalReference.1",
                            "metadata": {},
                            "name": "",
                            "available_range": {
                                "OTIO_SCHEMA": "TimeRange.1",
                                "duration": {
                                    "OTIO_SCHEMA": "RationalTime.1",
                                    "rate": 24.0,
                                    "value": 120.0
                                },
                                "start_time": {
                                    "OTIO_SCHEMA": "RationalTime.1",
                                    "rate": 24.0,
                                    "value": 0.0
                                }
                            },
                            "target_url": "file:///home/karthik/hello_world_example/media/hello_world.mp4"
                        }
                    },
                    {
                        "OTIO_SCHEMA": "Transition.1",
                        "metadata": {},
                        "name": "crossfade",
                        "in_offset": {
                            "OTIO_SCHEMA": "RationalTime.1",
                            "rate": 24.0,
                            "value": 6.0
                        },
                        "out_offset": {
                            "OTIO_SCHEMA": "RationalTime.1",
                            "rate": 24.0,
                            "value": 6.0
                        },
                        "transition_type": "SMPTE_Dissolve"
                    },
                    {
                        "OTIO_SCHEMA": "Clip.1",
                        "metadata": {},
                        "name": "welcome",
                        "source_range": {
                            "OTIO_SCHEMA": "TimeRange.1",
                            "duration": {
                                "OTIO_SCHEMA": "RationalTime.1",
                                "rate": 24.0,
                                "value": 42.0
                            },
                            "start_time": {
                                "OTIO_SCHEMA": "RationalTime.1",
                                "rate": 24.0,
                                "value": 6.0
                            }
                        },
                        "effects": [],
                        "markers": [],
                        "media_reference": {
                            "OTIO_SCHEMA": "ExternalReference.1",
                            "metadata": {},
                            "name": "",
                            "available_range": {
                                "OTIO_SCHEMA": "TimeRange.1",
                                "duration": {
                                    "OTIO_SCHEMA": "RationalTime.1",
                                    "rate": 24.0,
                                    "value": 120.0
                                },
                                "start_time": {
                                    "OTIO_SCHEMA": "RationalTime.1",
                                    "rate": 24.0,
                                    "value": 0.0
                                }
                            },
                            "target_url": "file:///home/karthik/hello_world_example/media/welcome.mp4"
                        }
                    }
                ],
                "kind": "Video"
            }
        ]
    }
}
```
