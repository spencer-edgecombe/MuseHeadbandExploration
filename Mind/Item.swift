//
//  Item.swift
//  Mind
//
//  Created by Spencer Edgecombe on 2023-11-08.
//

import Foundation
import SwiftData

@Model
final class Item {
    var timestamp: Date
    
    init(timestamp: Date) {
        self.timestamp = timestamp
    }
}
