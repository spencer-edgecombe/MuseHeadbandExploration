//
//  MuseConnectViewModel.swift
//  MuseStatsMac
//
//  Created by Gair Shields on 2023-01-03.
//

import SwiftUI

class MuseConnectViewModel: IXNLogListener, ObservableObject {
    var museManager: IXNMuseManager?
    var museListener: IXNMuseListener?
    var dataListener: IXNMuseDataListener?
    var connectionListener: IXNMuseConnectionListener?
    var selectedMuse: IXNMuse?
    @Published var selectedMuseName: String?
    @Published var museNames: [String] = []
    var logManager: IXNLogManager?
    var museList = [String: IXNMuse]()
    @Published var logs: [String] = []
    var points: [UnitPoint] = []
  
    init() {
        self.museNames.removeAll()
        self.logManager = IXNLogManager.instance()
        self.logManager?.setLogListener(self)
        self.museManager = IXNMuseManagerMac()
        self.museListener = MuseListener(parent: self)
        self.dataListener = DataListener(parent: self)
        self.connectionListener = ConnectionListener(parent: self)
        
        self.museManager?.removeFromList(after: 10)
        self.museManager?.setMuseListener(self.museListener)
        self.museManager?.startListening()
    }
    
    func museListChanged() {
        museList.removeAll()
        DispatchQueue.main.async { [weak self] in
            guard let self else { return }
            self.museNames.removeAll()
            self.selectedMuseName = nil
            if let muses = self.museManager?.getMuses() {
                for muse in muses {
                    self.museList[muse.getName()] = muse
                    self.museNames.append(muse.getName())
                    self.log(message: "Found \(muse.getName()) with ID: \(muse.getMacAddress())")
                }
                if self.museNames.count > 0 && self.selectedMuseName == nil {
                    self.selectedMuseName = self.museNames.first
                }
            }
        }
    }
    
    func getSelectedItem(combo: NSComboBox) -> String? {
        if combo.indexOfSelectedItem != -1 {
            return combo.itemObjectValue(at: combo.indexOfSelectedItem) as? String
        }
        return nil
    }
    
    func onScanClick() {
        self.museManager?.stopListening()
        self.museManager?.startListening()
    }
    
    func onConnectClick() {
        if let m = selectedMuseName {
            if let muse = museList[m] {
                if muse.getConnectionState() == .disconnected {
                    self.museManager?.stopListening()
                    muse.unregisterAllListeners()
                    muse.register(self.connectionListener)
                    muse.register(self.dataListener, type: .eeg)
                    muse.setPreset(IXNMusePreset.preset21)
                    muse.runAsynchronously()
                }
            }
        }
    }
    
    func onDisconnectClick() {
        if let muses = self.museManager?.getMuses() {
            for muse in muses {
                if muse.getConnectionState() == .connected {
                    muse.disconnect()
                }
            }
        }
    }
    
    func receive(_ packet: IXNMuseConnectionPacket, muse: IXNMuse?) {
        if packet.previousConnectionState == .connecting && packet.currentConnectionState == .disconnected {
            muse?.unregisterAllListeners()
            log(message: "\(muse?.getName() ?? "") disconnected")
            self.museManager?.startListening()
        }
        if packet.previousConnectionState == .connecting && packet.currentConnectionState == .connected {
            log(message: "\(muse?.getName() ?? "") connected")
        }
    }
    
    func receive(_ packet: IXNMuseDataPacket?, muse: IXNMuse?) {
        if packet != nil && packet!.packetType() == .eeg {
//            points.append(packet.)
        }
    }
    
    func receiveLog(_ log: IXNLogPacket) {
        self.logs.insert(log.message, at: 0)
    }
    
    func log(message: String) {
        self.logManager?.writeLog(IXNSeverity.sevDebug, raw: false, tag: "", message: message)
    }
    
    deinit {
//        self.graphView?.stop()
        self.museManager?.stopListening()
        if let muses = self.museManager?.getMuses() {
            for muse in muses {
                muse.unregisterAllListeners()
                if muse.getConnectionState() == .connected {
                    muse.disconnect()
                }
            }
        }
    }
}

class MuseListener: IXNMuseListener {
    var parent: MuseConnectViewModel
    
    init(parent: MuseConnectViewModel){
        self.parent = parent
    }
    
    func museListChanged() {
        self.parent.museListChanged()
    }
}

class ConnectionListener: IXNMuseConnectionListener {
    var parent: MuseConnectViewModel
    
    init(parent: MuseConnectViewModel){
        self.parent = parent
    }
    
    func receive(_ packet: IXNMuseConnectionPacket, muse: IXNMuse?) {
        parent.receive(packet, muse: muse)
    }
}

class DataListener: IXNMuseDataListener {
    var parent: MuseConnectViewModel
    
    init(parent: MuseConnectViewModel){
        self.parent = parent
    }
    
    func receive(_ packet: IXNMuseDataPacket?, muse: IXNMuse?) {
        parent.receive(packet, muse: muse)
    }
    
    func receive(_ packet: IXNMuseArtifactPacket, muse: IXNMuse?) {
    }
}
