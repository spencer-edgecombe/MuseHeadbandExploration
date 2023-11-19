//
//  EEGGraphView.swift
//  MuseStatsMac
//
//  Created by Gair Shields on 2023-01-07.
//

import SwiftUI

struct DataPoint {
    var value: Double
    var time: Int64
}

class EEGGraphView {
    let lock = NSLock()
    let maxPoints = 3500
    let maxSignal = 1800.0
    let refreshRate = 1.0 / 30
    let dataChannels: [IXNEeg] = [.EEG1, .EEG2, .EEG3, .EEG4]
    let darkColor: [IXNEeg: Color] = [.EEG1: .green, .EEG2: .red, .EEG3: .blue, .EEG4: .white]
    let lightColor: [IXNEeg: Color] = [.EEG1: .green, .EEG2: .purple, .EEG3: .blue, .EEG4: .gray]
    var dataPoints = [IXNEeg: [DataPoint]]()
    var updateTimer: Timer?
    
    init() {
        for ch in dataChannels {
            dataPoints[ch] = [DataPoint]()
        }
    }
    
//    override func draw(_ rect: NSRect) {
//        super.draw(rect)
//        for ch in dataChannels {
//            drawChannel(rect, channel: ch)
//        }
//        let context = NSGraphicsContext.current!.cgContext
//        context.setStrokeColor(Color.darkGray.cgColor)
//        context.setLineWidth(2.0)
//        context.addRect(rect)
//        context.strokePath()
//    }
    
    func drawChannel(_ rect: NSRect, channel: IXNEeg) {
        lock.lock()
        defer {
            lock.unlock()
        }
        let points = dataPoints[channel]!
        let maxPoints = points.count;
        let numPoints = min(Int(rect.width), maxPoints)
        var displayPoints = [Int]()
        let ySize = rect.height / CGFloat(dataChannels.count)
        let yScale = rect.height / (CGFloat(dataChannels.count) * maxSignal)
        
        if numPoints == 0 {
            return
        }
        
        let index = maxPoints - numPoints
        let offset = ySize * CGFloat(channel.rawValue) + ySize / 16;
        
        for n in 0...numPoints {
            let i = index + n
            if i >= maxPoints {
                break
            }
            displayPoints.append(Int((points[i].value * yScale) + offset))
        }
        
        let context = NSGraphicsContext.current!.cgContext
//        context.setStrokeColor(graphColor(channel: channel).cgColor)
        context.setLineWidth(1.0)
        
        // Move to the first point
        context.move(to: CGPoint(x: 0, y: displayPoints[0]))
        
        // Draw a line to each subsequent point
        for i in 1..<displayPoints.count {
            context.addLine(to: CGPoint(x: i, y: displayPoints[i]))
        }
        
        context.strokePath()
    }
    
    func addPoint(packet: IXNMuseDataPacket) {
        lock.lock()
        defer {
            lock.unlock()
        }
        for ch in dataChannels {
            if dataPoints[ch] != nil {
                dataPoints[ch]!.append(DataPoint(value: packet.getEegChannelValue(ch), time: packet.timestamp()))
                if dataPoints[ch]!.count > maxPoints {
                    dataPoints[ch]!.remove(at: 0)
                }
            }
        }
    }
    
    func start() {
        updateTimer = Timer.scheduledTimer(withTimeInterval: self.refreshRate, repeats: true) { [weak self] timer in
            self?.setNeedsDisplay(self?.bounds ?? NSRect.zero)
        }
    }
    
    func stop() {
        updateTimer?.invalidate()
        updateTimer = nil
    }
    
    func graphColor(channel: IXNEeg) -> Color {
        if NSApp.effectiveAppearance.name == NSAppearance.Name.darkAqua ||
            NSApp.effectiveAppearance.name == NSAppearance.Name.vibrantDark {
            return darkColor[channel]!
        }
        return lightColor[channel]!
    }
}
