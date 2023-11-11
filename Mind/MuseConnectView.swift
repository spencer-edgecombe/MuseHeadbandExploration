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
                    ForEach(viewModel.museNames, id: \.self) { name in
                        HStack {
                            Button {
                                viewModel.selectedMuseName = name
                            } label: {
                                if name == viewModel.selectedMuseName {
                                    Image(systemName: "checkmark.circle")
                                } else {
                                    Image(systemName: "circle")
                                }
                            }
                            Text(name)
                        }
                    }
            }
            Spacer()
        }
        .toolbar {
            Button("Scan") {
                viewModel.onScanClick()
            }
            Button("Connect") {
                viewModel.onConnectClick()
            }
            Button("Disconnect") {
                viewModel.onDisconnectClick()
            }
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
