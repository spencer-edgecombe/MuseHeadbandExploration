//
//  MuseConnectView.swift
//  Mind
//
//  Created by Spencer Edgecombe on 2023-11-10.
//

import SwiftUI

struct MuseConnectView: View {
    @ObservedObject var viewModel: MuseConnectViewModel
    var body: some View {
        HStack(alignment: .top) {
            VStack(alignment: .leading) {
                Group {
                    Image(systemName: viewModel.isConnected ? "waveform.slash" : "waveform")
                        .imageScale(.large)
                }
                Spacer()
            }
            Spacer()
        }
        .padding()
        .navigationSplitViewStyle(.balanced)
        .toolbarTitleDisplayMode(.inlineLarge)
        .navigationTitle("Headset")
    }
}

#Preview {
    NavigationSplitView {
    } detail: {
        MuseConnectView(viewModel: .init())
    }
}
