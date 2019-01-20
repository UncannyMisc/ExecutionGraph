import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { MatDialog } from '@angular/material';
import { ILogger, LoggerFactory } from '@eg/logger/src';
import { FileBrowserService } from '../../services';
import { DirectoryInfo, FileInfo, isFile } from '../../services/FileBrowserService';
import { ConfirmationDialogComponent } from '../confirmation-dialog/confirmation-dialog.component';

@Component({
  selector: 'eg-file-browser',
  templateUrl: './file-browser.component.html',
  styleUrls: ['./file-browser.component.scss']
})
export class FileBrowserComponent implements OnInit {
  private logger: ILogger;
  private initPath = '.';

  private rootPath: string;
  private atRoot: boolean;
  private isLoading = false;
  private parentPaths: string[] = [];

  private currentDirectory: DirectoryInfo = null;

  constructor(private browser: FileBrowserService, readonly loggerFactory: LoggerFactory, private dialog: MatDialog) {
    this.logger = loggerFactory.create('FileBrowserComponent');
  }

  @Input('allowSave') allowSave: boolean = true;
  @Input('allowOpen') allowOpen: boolean = true;
  @Input('allowDelete') allowDelete: boolean = true;

  @Output('onSaveFile') onSaveFile: EventEmitter<string>;
  @Output('onOpenFile') onOpenFile: EventEmitter<string>;
  @Output('onDeleteFile') onDeleteFile: EventEmitter<string>;

  ngOnInit() {
    this.openRoot();
  }

  private openRoot() {
    this.reset();
    this.loadDirectory(this.initPath).then(d => {
      this.rootPath = d.path;
      this.atRoot = true;
      this.currentDirectory = d;
    });
  }

  private reset() {
    this.atRoot = true;
    this.rootPath = undefined;
    this.parentPaths = [];
  }

  public openDirectory(dir: DirectoryInfo) {
    if (dir) {
      this.loadDirectory(dir.path).then(d => {
        this.parentPaths.push(this.currentDirectory.path);
        this.currentDirectory = d;
        this.atRoot = false;
      });
    }
  }

  public openParentDirectory() {
    const p = this.parentPaths[this.parentPaths.length - 1];
    if (p) {
      this.loadDirectory(p).then(d => {
        if (d.path == this.rootPath) {
          this.atRoot = true;
        }
        this.parentPaths.pop();
        this.currentDirectory = d;
      });
    }
  }

  private async loadDirectory(path: string): Promise<DirectoryInfo> {
    this.isLoading = true;
    this.logger.debug(`loadDirectory: '${path}'`);
    return this.browser.browse(path).then(pathInfo => {
      if (!isFile(pathInfo)) {
        this.isLoading = false;
        return pathInfo;
      } else {
        throw `Cannot browse to a file: ${pathInfo.path}`;
      }
    });
  }

  public notEmpty(dir: DirectoryInfo) {
    return !dir.explored || (dir.files.length > 0 || dir.directories.length > 0);
  }

  public openFile(file: FileInfo) {
    if (this.allowOpen) {
      this.logger.debug(`Opening file '${file.path}'`);
      this.onOpenFile.emit(file.path);
    } else {
      this.logger.error('Programming Error!');
      throw 'Error!';
    }
  }

  public deleteConfirm(path: FileInfo | DirectoryInfo) {
    const dialogRef = this.dialog.open(ConfirmationDialogComponent, {
      minWidth: '10%',
      data: {
        title: 'Delete',
        question: `Do you really want to delete the path '${path.path}' ?`
      }
    });
    dialogRef.afterClosed().subscribe(result => {
      if (result) {
        this.deleteFile(path);
      }
    });
  }

  public isFileOpenable(file: FileInfo) {
    return file.name.endsWith('.eg');
  }

  private deleteFile(path: FileInfo | DirectoryInfo) {
    if (this.allowDelete && this.isFileOpenable(path)) {
      this.logger.debug(`Deleting path '${path.path}'`);
      this.onDeleteFile.emit(path.path);
    } else {
      this.logger.error('Programming Error!');
      throw 'Error!';
    }
  }
}
