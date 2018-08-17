// =========================================================================================
//  ExecutionGraph
//  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//
//  @date Sun Jul 29 2018
//  @author Simon Spoerri, simon (døt) spoerri (at) gmail (døt) com
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
// =========================================================================================

import { HttpClientModule, HttpClient } from '@angular/common/http';

import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import {
  MatIconModule,
  MatToolbarModule,
  MatMenuModule,
  MatButtonModule,
  MatCheckboxModule,
  MatButtonToggleModule
} from '@angular/material';

import { VERBOSE_LOG_TOKEN } from './tokens';

import { GraphModule } from '@eg/graph';
import { SimpleConsoleLoggerFactory, LoggerFactory } from '@eg/logger';

import { BinaryHttpRouterService } from './services/BinaryHttpRouterService';
import { CefMessageRouterService } from './services/CefMessageRouterService';

import { ExecutionService } from './services/ExecutionService';
import { ExecutionServiceBinaryHttp } from './services/ExecutionServiceBinaryHttp';
import { ExecutionServiceDummy } from './services/ExecutionServiceDummy';

import { GeneralInfoService } from './services/GeneralInfoService';
import { GeneralInfoServiceDummy } from './services/GeneralInfoServiceDummy';
import { GeneralInfoServiceBinaryHttp } from './services/GeneralInfoServiceBinaryHttp';

import { GraphManipulationService } from './services/GraphManipulationService';
import { GraphManipulationServiceBinaryHttp } from './services/GraphManipulationServiceBinaryHttp';
import { GraphManipulationServiceDummy } from './services/GraphManipulationServiceDummy';

import { GraphManagementService } from './services/GraphManagementService';
import { GraphManagementServiceBinaryHttp } from './services/GraphManagementServiceBinaryHttp';
import { GraphManagementServiceDummy } from './services/GraphManagementServiceDummy';

import { TestService } from './services/TestService';

import { AppComponent } from './app.component';
import { ToolbarComponent } from './components/toolbar/toolbar.component';
import { WorkspaceComponent } from './components/workspace/workspace.component';

import { environment } from '../environments/environment';
import { ConnectionStyleOptionsComponent } from './components/connection-style-options/connection-style-options.component';

@NgModule({
  declarations: [AppComponent, ToolbarComponent, WorkspaceComponent, ConnectionStyleOptionsComponent],
  imports: [
    HttpClientModule,
    BrowserModule,
    BrowserAnimationsModule,
    MatIconModule,
    MatToolbarModule,
    MatMenuModule,
    MatButtonModule,
    MatButtonToggleModule,
    MatCheckboxModule,
    GraphModule
  ],
  providers: [
    BinaryHttpRouterService,
    CefMessageRouterService,
    TestService,
    { provide: VERBOSE_LOG_TOKEN, useValue: environment.logReponsesVerbose },
    { provide: LoggerFactory, useClass: SimpleConsoleLoggerFactory },
    {
      provide: ExecutionService,
      useClass: environment.production ? ExecutionServiceBinaryHttp : ExecutionServiceDummy
    },
    {
      provide: GeneralInfoService,
      useClass: environment.production ? GeneralInfoServiceBinaryHttp : GeneralInfoServiceDummy
    },
    {
      provide: GraphManipulationService,
      useClass: environment.production ? GraphManipulationServiceBinaryHttp : GraphManipulationServiceDummy
    },
    {
      provide: GraphManagementService,
      useClass: environment.production ? GraphManagementServiceBinaryHttp : GraphManagementServiceDummy
    }
  ],
  bootstrap: [AppComponent]
})
export class AppModule {}
