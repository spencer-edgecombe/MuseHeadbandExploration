//
//  MuseConnectViewModel.swift
//  Mind
//
//  Created by Spencer Edgecombe on 2023-11-10.
//

import Foundation
import SwiftUI
import Combine

class MuseConnectViewModel: ObservableObject {
    // Published properties to update the UI
    var museMap: [String: IXNMuse] = [:] {
        didSet {
            RunLoop.main.perform { [weak self] in
                guard let self else { return }
                self.museList = Array(self.museMap.keys.sorted())
            }
        }
    }
    @Published var museList: [String] = []
    @Published var selectedMuseName: String?
    @Published var logMessages: [String] = []
    @Published var isConnected: Bool = false

    // Muse manager and listeners
    private var museManager: IXNMuseManager?
    private var dataListener: IXNMuseDataListener?
    private var connectionListener: IXNMuseConnectionListener?
    private var museMapener: IXNMuseListener?

    init() {
        setupMuseManager()
    }

    private func setupMuseManager() {
        // Initialize the Muse manager and listeners
        self.museManager = IXNMuseManagerMac()
        self.museMapener = MuseListener(viewModel: self)
        self.dataListener = DataListener(viewModel: self)
        self.connectionListener = ConnectionListener(viewModel: self)

        // Setup the manager
        self.museManager?.removeFromList(after: 10)
        self.museManager?.setMuseListener(self.museMapener)
    }
    
    func startListening() {
        self.museManager?.startListening()
    }

    func updateMuseList() {
        DispatchQueue.main.async {
            self.museMap.removeAll()
            guard let muses = self.museManager?.getMuses() else {
                return
            }
            for muse in muses {
                let name = muse.getName()
                self.museMap[name] = muse
                self.log(message: "Found \(name) with ID: \(muse.getMacAddress())")
            }
        }
    }

    func connectToSelectedMuse() {
        guard let selectedName = selectedMuseName, let muse = museMap[selectedName] else { return }
        if muse.getConnectionState() == .disconnected {
            self.museManager?.stopListening()
            muse.unregisterAllListeners()
            muse.register(self.connectionListener)
            muse.register(self.dataListener, type: .eeg)
            muse.setPreset(IXNMusePreset.preset21)
            muse.runAsynchronously()
        }
    }

    func disconnectAllMuses() {
        if let muses = self.museManager?.getMuses() {
            for muse in muses {
                if muse.getConnectionState() == .connected {
                    muse.disconnect()
                }
            }
        }
    }

    func log(message: String) {
        DispatchQueue.main.async {
            self.logMessages.insert(message, at: 0)
        }
    }

    deinit {
        // Clean-up code
    }
}

// Listener classes
class MuseListener: IXNMuseListener {
    func museListChanged() {
        
    }
    
    weak var viewModel: MuseConnectViewModel?

    init(viewModel: MuseConnectViewModel) {
        self.viewModel = viewModel
    }

    func museMapChanged() {
        viewModel?.updateMuseList()
    }
}

class ConnectionListener: IXNMuseConnectionListener {
    weak var viewModel: MuseConnectViewModel?

    init(viewModel: MuseConnectViewModel) {
        self.viewModel = viewModel
    }

    func receive(_ packet: IXNMuseConnectionPacket, muse: IXNMuse?) {
        // Handle connection updates
    }
}

class DataListener: IXNMuseDataListener {
    
    weak var viewModel: MuseConnectViewModel?

    init(viewModel: MuseConnectViewModel) {
        self.viewModel = viewModel
    }

    func receive(_ packet: IXNMuseDataPacket?, muse: IXNMuse?) {
        // Handle data updates
    }
    
    func receive(_ packet: IXNMuseArtifactPacket, muse: IXNMuse?) {
        
    }
}
