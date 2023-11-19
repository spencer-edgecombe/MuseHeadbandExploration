//
//  MindApp.swift
//  Mind
//
//  Created by Spencer Edgecombe on 2023-11-08.
//

import SwiftUI
import SwiftData

@main
struct MindApp: App {
    var sharedModelContainer: ModelContainer = {
        let schema = Schema([
            Item.self,
        ])
        let modelConfiguration = ModelConfiguration(schema: schema, isStoredInMemoryOnly: false)

        do {
            return try ModelContainer(for: schema, configurations: [modelConfiguration])
        } catch {
            fatalError("Could not create ModelContainer: \(error)")
        }
    }()

    var connectViewModel: MuseConnectViewModel = MuseConnectViewModel()
    var body: some Scene {
        WindowGroup {
            MuseConnectView(viewModel: connectViewModel)
        }
        .modelContainer(sharedModelContainer)
        .windowResizability(.contentSize)

    }
}
