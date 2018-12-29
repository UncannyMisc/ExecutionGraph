import { Injectable } from '@angular/core';
import { Effect, Actions } from '@ngrx/effects';

import { tap } from 'rxjs/operators';

import { MatSnackBar } from '@angular/material';
import { ShowNotification, SHOW_NOTIFICATION } from '../actions/notification.actions';


@Injectable()
export class NotificationEffects {
    constructor(
        private actions$: Actions,
        private snackBar: MatSnackBar,
    ) {}

    @Effect({ dispatch: false })
    showNotification$ = this.actions$.ofType<ShowNotification>(SHOW_NOTIFICATION)
        .pipe(
            tap(action => this.snackBar.open(action.text, '', { duration: action.showTimeMs }))
        );
}
