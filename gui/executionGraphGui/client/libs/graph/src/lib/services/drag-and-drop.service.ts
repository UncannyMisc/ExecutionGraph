import { DroppableDirective } from "../directives/droppable.directive";
import { DraggableDirective, DragEvent } from "../directives/draggable.directive";

export class DragAndDropService {
    private readonly droppables: DroppableDirective[] = [];

    public registerDroppable(droppable: DroppableDirective) {
        if (this.droppables.indexOf(droppable) >= 0) {
            throw new Error(`Droppable cannot be registered because it is already registered`);
        }
        this.droppables.push(droppable);
    }

    public deregisterDroppable(droppable: DroppableDirective) {
        if(this.droppables.indexOf(droppable) < 0) {
            throw new Error(`Droppable cannot be deregistered because it is not registered`);
        }
        this.droppables.splice(this.droppables.indexOf(droppable), 1);
    }

    public startTracking(draggable: DraggableDirective) {
        this.droppables.forEach(droppable => droppable.startTracking(draggable));
    }

    public stopTracking(dragEvent: DragEvent) {
        this.droppables.forEach(droppable => droppable.stopTracking(dragEvent));
    }
}