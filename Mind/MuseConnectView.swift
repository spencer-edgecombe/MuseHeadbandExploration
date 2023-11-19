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
        Spacer()
        Divider()
        ScrollView {
          VStack {
            ForEach(viewModel.logs, id: \.self) { log in
              Text(log)
            }
          }
        }
        .frame(height: 100)
      }
      Spacer()
    }
    .toolbar {
      Text("Connect to Muse")
      Toggle(isOn: $viewModel.shouldConnect) {
        Text("Connect to Muse")
      }
      .toggleStyle(.switch)
      Image(systemName: connectionImageName)
        .foregroundColor(connectionImageTint)
        .imageScale(.large)
    }
    .toolbarRole(.editor)
    .padding()
    .navigationSplitViewStyle(.balanced)
    .toolbarTitleDisplayMode(.inlineLarge)
    .navigationTitle("Headset")
  }

  var connectionImageName: String {
    viewModel.isConnected ? "waveform" : "waveform.slash"
  }

  var connectionImageTint: Color {
    viewModel.isConnected ? .green : .gray
  }
}

struct MusePreview: View {
  var viewModel: MuseConnectViewModel
  init() {
    viewModel = MuseConnectViewModel()
  }

  var body: some View {
    MuseConnectView(viewModel: viewModel)
  }
}

struct MuseConnectView_Previews: PreviewProvider {
  static var previews: some View {
    MusePreview()
  }

}
