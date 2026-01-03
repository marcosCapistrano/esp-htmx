/**
 * @typedef {Object} TemperatureSensor
 * @property {string} designator - Component reference designator
 */

/**
 * @typedef {Object} BoardConfig
 * @property {string} name - Board display name
 * @property {number} chipCount - Total number of chips
 * @property {number[][]} chipGrid - Chip numbers organized by rows
 * @property {TemperatureSensor[]} tempSensors - Temperature sensor designators
 * @property {number} gridColumns - Number of columns in chip grid
 */

/** @type {Record<string, BoardConfig>} */
export const boardConfigs = {
  's19': {
    name: 'S19',
    chipCount: 76,
    gridColumns: 9,
    chipGrid: [
      [-1, 2, 3, 6, 7, 10, 11, 14, 15],
      [-1, 1, 4, 5, 8, 9, 12, 13, 16],
      [33, 32, 29, 28, 25, 24, 21, 20, 17],
      [34, 31, 30, 27, 26, 23, 22, 19, 18],
    ],
    tempSensors: [
      { designator: 'U4' },
      { designator: 'U5' },
      { designator: 'U6' },
      { designator: 'U7' },
    ],
  },
  's21': {
    name: 'S21',
    chipCount: 108,
    gridColumns: 12,
    chipGrid: [
      [  9, 10, 27, 28, 45, 46, 63, 64, 81, 82,  99, 100],
      [  8, 11, 26, 29, 44, 47, 62, 65, 80, 83,  98, 101],
      [  7, 12, 25, 30, 43, 48, 61, 66, 79, 84,  97, 102],
      [  6, 13, 24, 31, 42, 49, 60, 67, 78, 85,  96, 103],
      [  5, 14, 23, 32, 41, 50, 59, 68, 77, 86,  95, 104],
      [  4, 15, 22, 33, 40, 51, 58, 69, 76, 87,  94, 105],
      [  3, 16, 21, 34, 39, 52, 57, 70, 75, 88,  93, 106],
      [  2, 17, 20, 35, 38, 53, 56, 71, 74, 89,  92, 107],
      [  1, 18, 19, 36, 37, 54, 55, 72, 73, 90,  91, 108],
    ],
    tempSensors: [
      { designator: 'U4' },
      { designator: 'U5' },
    ],
  },
};

/**
 * Get board configuration by name
 * @param {string} boardName
 * @returns {BoardConfig | undefined}
 */
export function getBoardConfig(boardName) {
  return boardConfigs[boardName.toLowerCase()];
}
