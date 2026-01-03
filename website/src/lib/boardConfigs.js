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
    chipCount: 100,
    gridColumns: 10,
    chipGrid: [
      // TODO: Add S21 chip layout
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
