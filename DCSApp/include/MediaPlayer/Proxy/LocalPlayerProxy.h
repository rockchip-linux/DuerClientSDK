/*
 * Copyright (c) 2017 Baidu, Inc. All Rights Reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef DUEROS_DCS_APP_MEDIAPLAYER_LOCALPLAYERPROXY_H_
#define DUEROS_DCS_APP_MEDIAPLAYER_LOCALPLAYERPROXY_H_

#include <DcsSdk/MediaPlayerInterface.h>

#include "Mp3FilePlayerInterface.h"

namespace duerOSDcsApp {
namespace mediaPlayer {

using duerOSDcsSDK::sdkInterfaces::AttachmentReader;

class LocalPlayerProxy : public duerOSDcsSDK::sdkInterfaces::LocalSourcePlayerInterface,
    public duerOSDcsSDK::sdkInterfaces::MediaPlayerInterface,
    public AudioPlayerListener {
public:
    static std::shared_ptr<LocalPlayerProxy> create(const std::string& audio_device = "default");

    ~LocalPlayerProxy();

    void playLocalSource(const std::string& source,
                         bool needFocus,
                         void (*start_callback)(void* arg),
                         void* start_cb_arg,
                         void (*finish_callback)()) override;

    void playTts(const std::string& content, bool needFocus, void (*callback)()) override;

    duerOSDcsSDK::sdkInterfaces::MediaPlayerStatus setSource(
        std::shared_ptr<AttachmentReader> attachmentReader) override;

    duerOSDcsSDK::sdkInterfaces::MediaPlayerStatus setSource(const std::string& url) override;

    duerOSDcsSDK::sdkInterfaces::MediaPlayerStatus setSource(const std::string& audio_source,
            bool repeat) override;

    void setObserver(
        std::shared_ptr<duerOSDcsSDK::sdkInterfaces::MediaPlayerObserverInterface> playerObserver) override;

    void setLocalPlayObserver(
        std::shared_ptr<duerOSDcsSDK::sdkInterfaces::LocalSourcePlayerInterface> playerObserver);

    duerOSDcsSDK::sdkInterfaces::MediaPlayerStatus setOffset(std::chrono::milliseconds offset) override;

    duerOSDcsSDK::sdkInterfaces::MediaPlayerStatus play() override;

    duerOSDcsSDK::sdkInterfaces::MediaPlayerStatus stop() override;

    duerOSDcsSDK::sdkInterfaces::MediaPlayerStatus pause() override;

    duerOSDcsSDK::sdkInterfaces::MediaPlayerStatus resume() override;

    std::chrono::milliseconds getOffset() override;

    void setImpl(std::shared_ptr<Mp3FilePlayerInterface> impl);

private:
    LocalPlayerProxy(const std::string& audio_device);

    bool init();

    void playbackStarted(int offset_ms) override;

    void playbackStopped(int offset_ms) override;

    void playbackPaused(int offset_ms) override;

    void playbackResumed(int offset_ms) override;

    void playbackNearlyFinished(int offset_ms) override;

    void playbackFinished(int offset_ms, AudioPlayerFinishStatus status) override;

    void playbackProgress(int offset_ms) override;

    void playbackStreamUnreach() override;

    void playbackError() override;

    void reportBufferTime(long time) override;

private:
    std::string m_resPath;

    std::shared_ptr<duerOSDcsSDK::sdkInterfaces::MediaPlayerObserverInterface> m_playerObserver;

    std::shared_ptr<duerOSDcsSDK::sdkInterfaces::LocalSourcePlayerInterface> m_localPlayer;

    void (*m_playStartFunc)(void* arg);

    void (*m_playFinishFunc)();

    void* m_argPtr;

    std::shared_ptr<Mp3FilePlayerInterface> m_impl;
};

}  // mediaPlayer
}  // duerOSDcsApp

#endif  // DUEROS_DCS_APP_MEDIAPLAYER_LOCALPLAYERPROXY_H_
